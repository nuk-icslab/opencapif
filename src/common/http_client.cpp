#include "http_client.h"

namespace capif {

httpException::httpException(const std::string &msg) : error_msg(msg){};
const char *httpException::what() const throw() { return error_msg.c_str(); }

static size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append(static_cast<char *>(ptr), size * nmemb);
  return size * nmemb;
}

httpClient::httpClient() : httpClient("CAPIF Client"){};

httpClient::httpClient(const char *_user_agent) : user_agent(_user_agent) {
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
}

httpClient::~httpClient(){

};

bool httpClient::init_curl() {
  /* get a curl handle */
  curl = curl_easy_init();
#if DEBUG_CURL
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  }
#endif
  return (bool)(curl);
}

std::string httpClient::get(std::string url, nlohmann::json params) {
  std::string res;
  if (init_curl()) {
    std::string query_params = "";
    if (!params.empty()) {
      for (auto &param : params.items()) {
        query_params += fmt::format("&{}={}", (std::string)param.key(),
                                    (std::string)param.value());
      }
      query_params = query_params.substr(1);
    }
    url += "?";
    url += query_params;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, true);

    res = request();
  }
  return res;
};
std::string httpClient::post(std::string url, nlohmann::json params) {
  std::string res;
  if (init_curl()) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, true);
    curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, params.dump().c_str());

    res = request();
  }
  return res;
};

std::string httpClient::request() {
  CURLcode res_code;
  std::string res;

  struct curl_slist *hs = NULL;
  hs = curl_slist_append(hs, "Content-Type: application/json");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

  /* Perform HTTP request */
  res_code = curl_easy_perform(curl);
  if (res_code != CURLE_OK) {
    std::string error_msg = fmt::format("curl_easy_perform() failed: {}",
                                        curl_easy_strerror(res_code));
    /* always cleanup */
    curl_easy_cleanup(curl);
    throw(httpException(error_msg));
  } else {
    /* always cleanup */
    curl_easy_cleanup(curl);
    return res;
  }
};
}  // namespace capif