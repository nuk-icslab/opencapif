#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

#include <nlohmann/json.hpp>
#include <vector>

#include "capif/model/AefProfile.h"
#include "capif/model/ServiceAPIDescription.h"
#include "capif/model/Version.h"
#include "http_client.h"
#include "invoker.h"

using namespace org::openapitools::server::model;

int main() {
  capif::httpClient httpClient{"Simple CAPIF API invoker"};

  capif::invoker::apiInvoker invoker{httpClient};
  invoker.onboard();

  std::string target_api = "simple-apis";
  std::string target_resource = "/ping";
  try {
    std::string res;
    res = invoker.call_api(target_api, target_resource, capif::invoker::GET,
                           nlohmann::json{});
    spdlog::info("Response: {}", res);
  } catch (capif::invoker::apiNotFoundException &e) {
    spdlog::error("Calling API {}: {}", target_api, e.what());
  }

  invoker.offboard();

  return 0;
}