#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

#include <nlohmann/json.hpp>
#include <vector>

#include "apf.h"
#include "capif/model/AefProfile.h"
#include "capif/model/ServiceAPIDescription.h"
#include "capif/model/Version.h"

using namespace org::openapitools::server::model;

namespace YAML {
template <>
struct convert<AefProfile> {
  static bool decode(const Node& node, AefProfile& rhs) {
    rhs.setAefId(node["aef_id"].as<std::string>());
    rhs.setDomainName(node["domain"].as<std::string>());

    Protocol proto;
    nlohmann::json proto_json = node["protocol"].as<std::string>();
    from_json(proto_json, proto);
    rhs.setProtocol(proto);

    std::vector<InterfaceDescription> ifaces;
    InterfaceDescription iface;
    const YAML::Node& ifaces_yaml = node["interfaces"];
    for (YAML::const_iterator it = ifaces_yaml.begin(); it != ifaces_yaml.end();
         ++it) {
      iface = it->as<InterfaceDescription>();
      ifaces.push_back(iface);
    }
    rhs.setInterfaceDescriptions(ifaces);

    std::vector<Version> versions;
    Version version;
    const YAML::Node& versions_yaml = node["versions"];
    for (YAML::const_iterator it = versions_yaml.begin();
         it != versions_yaml.end(); ++it) {
      version.setApiVersion(it->as<std::string>());
      versions.push_back(version);
    }
    rhs.setVersions(versions);

    return true;
  }
};
template <>
struct convert<InterfaceDescription> {
  static bool decode(const Node& node, InterfaceDescription& rhs) {
    if (!node["ipv4"] || !node["port"]) {
      return false;
    }

    rhs.setIpv4Addr(node["ipv4"].as<std::string>());
    rhs.setPort(node["port"].as<int>());
    return true;
  }
};
}  // namespace YAML

int main() {
  YAML::Node apf_config = YAML::LoadFile("config/apf.yaml");
  YAML::Node api_config = YAML::LoadFile("config/api.yaml");
  capif::apf::apiPublishingFunction apf{
      apf_config["apf_id"].as<std::string>()};  // Initialized with APF ID

  std::vector<AefProfile> aefs;
  AefProfile aef;
  const YAML::Node& aefs_yaml = apf_config["aefs"];
  spdlog::info("Avalible AEFs:");
  for (YAML::const_iterator it = aefs_yaml.begin(); it != aefs_yaml.end();
       ++it) {
    aef = it->as<AefProfile>();
    aefs.push_back(aef);

    nlohmann::json aef_json_obj;
    to_json(aef_json_obj, aef);
    spdlog::info(aef_json_obj.dump().c_str());
  }

  ServiceAPIDescription new_api;
  const YAML::Node& apis_yaml = api_config["paths"];
  for (YAML::const_iterator it = apis_yaml.begin(); it != apis_yaml.end();
       ++it) {
    std::string endpoint = it->first.as<std::string>();
    spdlog::info("Registering resource {} of service API \"{}\" (version: {})",
                 endpoint, api_config["info"]["title"].as<std::string>(),
                 api_config["info"]["version"].as<std::string>());

    new_api.setAefProfiles(aefs);
    new_api.setApiName(endpoint.substr(1));

    apf.register_api(new_api);
  }
  return 0;
}