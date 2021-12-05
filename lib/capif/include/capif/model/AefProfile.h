/**
 * CAPIF_Publish_Service_API
 * API for publishing service APIs. © 2021, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.0-alpha.2
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * AefProfile.h
 *
 * Represents the AEF profile data.
 */

#ifndef AefProfile_H_
#define AefProfile_H_

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "InterfaceDescription.h"
#include "SecurityMethod.h"
#include "capif/model/DataFormat.h"
#include "capif/model/Protocol.h"
#include "capif/model/Version.h"

namespace org::openapitools::server::model {

/// <summary>
/// Represents the AEF profile data.
/// </summary>
class AefProfile {
 public:
  AefProfile();
  virtual ~AefProfile() = default;

  /// <summary>
  /// Validate the current data in the model. Throws a ValidationException on
  /// failure.
  /// </summary>
  void validate() const;

  /// <summary>
  /// Validate the current data in the model. Returns false on error and writes
  /// an error message into the given stringstream.
  /// </summary>
  bool validate(std::stringstream& msg) const;

  /// <summary>
  /// Helper overload for validate. Used when one model stores another model and
  /// calls it's validate. Not meant to be called outside that case.
  /// </summary>
  bool validate(std::stringstream& msg, const std::string& pathPrefix) const;

  bool operator==(const AefProfile& rhs) const;
  bool operator!=(const AefProfile& rhs) const;

  /////////////////////////////////////////////
  /// AefProfile members

  /// <summary>
  /// Identifier of the API exposing function
  /// </summary>
  std::string getAefId() const;
  void setAefId(std::string const& value);
  /// <summary>
  /// API version
  /// </summary>
  std::vector<Version> getVersions() const;
  void setVersions(std::vector<Version> const& value);
  /// <summary>
  ///
  /// </summary>
  Protocol getProtocol() const;
  void setProtocol(Protocol const& value);
  bool protocolIsSet() const;
  void unsetProtocol();
  /// <summary>
  ///
  /// </summary>
  DataFormat getDataFormat() const;
  void setDataFormat(DataFormat const& value);
  bool dataFormatIsSet() const;
  void unsetDataFormat();
  /// <summary>
  /// Security methods supported by the AEF
  /// </summary>
  std::vector<SecurityMethod> getSecurityMethods() const;
  void setSecurityMethods(std::vector<SecurityMethod> const& value);
  bool securityMethodsIsSet() const;
  void unsetSecurityMethods();
  /// <summary>
  /// Domain to which API belongs to
  /// </summary>
  std::string getDomainName() const;
  void setDomainName(std::string const& value);
  bool domainNameIsSet() const;
  void unsetDomainName();
  /// <summary>
  /// Interface details
  /// </summary>
  std::vector<InterfaceDescription> getInterfaceDescriptions() const;
  void setInterfaceDescriptions(std::vector<InterfaceDescription> const& value);
  bool interfaceDescriptionsIsSet() const;
  void unsetInterfaceDescriptions();

  friend void to_json(nlohmann::json& j, const AefProfile& o);
  friend void from_json(const nlohmann::json& j, AefProfile& o);

 protected:
  std::string m_AefId;

  std::vector<Version> m_Versions;

  Protocol m_Protocol;
  bool m_ProtocolIsSet;
  DataFormat m_DataFormat;
  bool m_DataFormatIsSet;
  std::vector<SecurityMethod> m_SecurityMethods;
  bool m_SecurityMethodsIsSet;
  std::string m_DomainName;
  bool m_DomainNameIsSet;
  std::vector<InterfaceDescription> m_InterfaceDescriptions;
  bool m_InterfaceDescriptionsIsSet;
};

}  // namespace org::openapitools::server::model

#endif /* AefProfile_H_ */