#ifndef APF_H
#define APF_H

#include "capif/model/ServiceAPIDescription.h"

namespace capif::apf {
using namespace org::openapitools::server::model;
class apiPublishingFunction {
 public:
  apiPublishingFunction(std::string _apfId);
  ~apiPublishingFunction();
  void register_api(ServiceAPIDescription serviceAPIDescription);

 private:
  const std::string apfId;
  const std::string ccfRoot = "http://localhost:8080";
};
}  // namespace capif::apf

#endif