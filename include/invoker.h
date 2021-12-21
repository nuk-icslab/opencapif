#ifndef CAPIF_INVOKER_H
#define CAPIF_INVOKER_H

#include <optional>
#include <vector>

#include "capif/model/ServiceAPIDescription.h"
#include "http_client.h"

namespace capif::invoker {
using namespace org::openapitools::server::model;

struct apiNotFoundException : public std::exception {
  const char *what() const throw();
};

enum httpMethod { GET, POST, PUT, DELETE };

class apiInvoker {
 public:
  apiInvoker(capif::httpClient &_httpClient);
  ~apiInvoker();
  void onboard();
  void offboard();
  std::string call_api(std::string name, std::string resource,
                       httpMethod method, nlohmann::json params);

 private:
  capif::httpClient httpClient;
  bool onboarded;
  std::string invokerId;
  const std::string ccfRoot = "http://localhost:8080";
  std::vector<ServiceAPIDescription> avaliable_apis;

  void discover_apis();
  std::optional<ServiceAPIDescription> is_api_existed(std::string name);
};
}  // namespace capif::invoker

#endif