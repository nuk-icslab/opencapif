#ifndef CAPIF_HTTP_CLIENT_H
#define CAPIF_HTTP_CLIENT_H

#include <curl/curl.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>

namespace capif {

class httpException : public std::exception {
 public:
  explicit httpException(const std::string &msg);
  const char *what() const throw();

 protected:
  const std::string error_msg;
};

class httpClient {
 public:
  httpClient(const char *_user_agent);
  httpClient();
  ~httpClient();
  std::string get(std::string url, nlohmann::json param);
  std::string post(std::string url, nlohmann::json param);

 private:
  CURL *curl;
  const char *user_agent;
  bool init_curl();
  std::string request();
};
}  // namespace capif

#endif
