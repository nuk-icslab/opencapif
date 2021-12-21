#include "invoker.h"

#include <curl/curl.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>
#include <optional>
#include <random>
#include <sstream>
#include <vector>

namespace capif::invoker {
using namespace org::openapitools::server::model;

const char *apiNotFoundException::what() const throw() {
  return "API not found";
}

static std::string gen_uid(int n) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 15);
  std::stringstream ss;
  ss << std::hex;
  for (int i = 0; i < n; i++) {
    ss << dis(gen);
  }
  return ss.str();
}

static const char *to_string(httpMethod method) {
  switch (method) {
    case GET:
      return "GET";
    case POST:
      return "POST";
    case DELETE:
      return "DELETE";
    case PUT:
      return "PUT";
    default:
      return "Invalid method";
  }
}

apiInvoker::apiInvoker(capif::httpClient &_httpClient)
    : httpClient(_httpClient) {}

apiInvoker::~apiInvoker() {}
void apiInvoker::onboard() {
  /*
   * [TODO] Procedure of onboarding API invoker
   */
  onboarded = true;
  invokerId = gen_uid(5);
  discover_apis();
};
void apiInvoker::offboard() {
  /*
   * [TODO] Procedure of offboarding API invoker
   */
  onboarded = false;
};
std::string apiInvoker::call_api(std::string name, std::string resource,
                                 httpMethod method, nlohmann::json params) {
  std::optional<ServiceAPIDescription> api = is_api_existed(name);
  nlohmann::json json_obj;
  if (!api) throw apiNotFoundException{};
  to_json(json_obj, *api);

  AefProfile default_aef = api->getAefProfiles()[0];
  InterfaceDescription default_iface =
      default_aef.getInterfaceDescriptions()[0];
  std::string api_root = fmt::format("{}:{}", default_iface.getIpv4Addr(),
                                     default_iface.getPort());
  std::string api_version = default_aef.getVersions()[0].getApiVersion();

  std::string url =
      fmt::format("http://{}/{}/{}{}", api_root, name, api_version, resource);

  spdlog::info("API called \"{} {}\" data: {}", to_string(method), url,
               params.dump());
  switch (method) {
    case GET:
      httpClient.get(url, params);
      break;
    case POST:
      httpClient.post(url, params);
      break;

    default:
      spdlog::error("Not implemented");
      break;
  }

  return "";
}
void apiInvoker::discover_apis() {
  std::string res;
  std::string query_url =
      fmt::format("{}/service-apis/v1/allServiceAPIs", ccfRoot);
  nlohmann::json query_param;
  query_param["api-invoker-id"] = invokerId;

  try {
    res = httpClient.get(query_url, query_param);
  } catch (capif::httpException &e) {
    spdlog::error(e.what());
  }

  /* Parse the result */
  avaliable_apis = {};
  auto apis_json = nlohmann::json::parse(res);
  apis_json = apis_json["serviceAPIDescriptions"];
  ServiceAPIDescription api;

  for (auto api_json : apis_json) {
    from_json(api_json, api);
    avaliable_apis.push_back(api);
  }

  spdlog::info("Discovered {} APIs from CAPIF core function",
               avaliable_apis.size());

  return;
};
std::optional<ServiceAPIDescription> apiInvoker::is_api_existed(
    std::string name) {
  bool found = false;
  ServiceAPIDescription ret;
  for (ServiceAPIDescription api : avaliable_apis) {
    if (api.getApiName() == name) {
      found = true;
      ret = api;
    }
  }
  return found ? std::optional<ServiceAPIDescription>{ret} : std::nullopt;
}
}  // namespace capif::invoker
