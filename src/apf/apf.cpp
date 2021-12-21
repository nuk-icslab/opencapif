#include "apf.h"

#include <curl/curl.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>

namespace capif::apf {
using namespace org::openapitools::server::model;

apiPublishingFunction::apiPublishingFunction(std::string _apfId,
                                             capif::httpClient &_httpClient)
    : apfId(_apfId), httpClient(_httpClient) {}

apiPublishingFunction::~apiPublishingFunction() {}
void apiPublishingFunction::register_api(
    ServiceAPIDescription serviceAPIDescription) {
  std::string res;
  nlohmann::json api_json_obj;
  to_json(api_json_obj, serviceAPIDescription);
#if DEBUG
  spdlog::info(api_json_obj.dump().c_str());
#endif

  std::string publish_url =
      fmt::format("{}/published-apis/v1/{}/service-apis", ccfRoot, apfId);
  try {
    res = httpClient.post(publish_url, api_json_obj);
  } catch (capif::httpException &e) {
    spdlog::error(e.what());
  }

  spdlog::info("Successfully registered. Response from CCF: {}", res);
}
}  // namespace capif::apf
