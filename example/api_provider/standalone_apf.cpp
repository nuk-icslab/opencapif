#include <vector>

#include "apf.h"
#include "capif/model/AefProfile.h"
#include "capif/model/ServiceAPIDescription.h"
#include "capif/model/Version.h"

using namespace org::openapitools::server::model;

int main() {
  capif::apf::apiPublishingFunction apf{"test_APF"};  // Initialized with APF ID

  std::vector<AefProfile> aefs;
  AefProfile new_aef;
  ServiceAPIDescription new_api;
  std::vector<Version> versions;
  Version current_version;

  current_version.setApiVersion("v1");
  versions.push_back(current_version);

  new_aef.setAefId("test_aef");
  new_aef.setDomainName("localhost:8081");
  new_aef.setVersions(versions);
  aefs.push_back(new_aef);

  new_api.setApiName("test_api");
  new_api.setAefProfiles(aefs);

  apf.register_api(new_api);
  return 0;
}