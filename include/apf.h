#ifndef APF_H
#define APF_H

#include "capif/model/ServiceAPIDescription.h"
#include "http_client.h"

namespace capif::apf {
using namespace org::openapitools::server::model;
class apiPublishingFunction {
 public:
  apiPublishingFunction(std::string _apfId, capif::httpClient &_httpClient);
  ~apiPublishingFunction();
  void register_api(ServiceAPIDescription serviceAPIDescription);

 private:
  capif::httpClient httpClient;
  const std::string apfId;
  const std::string ccfRoot = "http://localhost:8080";
};
}  // namespace capif::apf

#endif