#include "apf.h"

#include <curl/curl.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>

namespace capif::apf {
using namespace org::openapitools::server::model;

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append(static_cast<char *>(ptr), size * nmemb);
  return size * nmemb;
}

apiPublishingFunction::apiPublishingFunction(std::string _apfId)
    : apfId(_apfId) {
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
}

apiPublishingFunction::~apiPublishingFunction() { curl_global_cleanup(); }
void apiPublishingFunction::register_api(
    ServiceAPIDescription serviceAPIDescription) {
  CURL *curl;
  CURLcode res_code;
  std::string res;

  nlohmann::json api_json_obj;
  to_json(api_json_obj, serviceAPIDescription);
  spdlog::info(api_json_obj.dump().c_str());

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl) {
    std::string publish_url =
        fmt::format("{}/published-apis/v1/{}/service-apis", ccfRoot, apfId);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, publish_url.c_str());

    curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, api_json_obj.dump().c_str());

    struct curl_slist *hs = NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

    /* Perform HTTP request */
    res_code = curl_easy_perform(curl);
    if (res_code != CURLE_OK) {
      spdlog::error("curl_easy_perform() failed: {}",
                    curl_easy_strerror(res_code));
    } else {
      spdlog::info("Successfully registered. Response from CCF: {}", res);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
}
}  // namespace capif::apf
