/**
 * CAPIF_Discover_Service_API
 * API for discovering service APIs. © 2021, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.0-alpha.1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * CustomOperation.h
 *
 * Represents the description of a custom operation.
 */

#ifndef CustomOperation_H_
#define CustomOperation_H_

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "capif/model/CommunicationType.h"
#include "capif/model/Operation.h"

namespace org::openapitools::server::model {

/// <summary>
/// Represents the description of a custom operation.
/// </summary>
class CustomOperation {
 public:
  CustomOperation();
  virtual ~CustomOperation() = default;

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

  bool operator==(const CustomOperation& rhs) const;
  bool operator!=(const CustomOperation& rhs) const;

  /////////////////////////////////////////////
  /// CustomOperation members

  /// <summary>
  ///
  /// </summary>
  CommunicationType getCommType() const;
  void setCommType(CommunicationType const& value);
  /// <summary>
  /// it is set as {custOpName} part of the URI structure for a custom operation
  /// without resource association as defined in subclause 4.4 of 3GPP
  /// TS 29.501.
  /// </summary>
  std::string getCustOpName() const;
  void setCustOpName(std::string const& value);
  /// <summary>
  /// Supported HTTP methods for the API resource. Only applicable when the
  /// protocol in AefProfile indicates HTTP.
  /// </summary>
  std::vector<Operation> getOperations() const;
  void setOperations(std::vector<Operation> const& value);
  bool operationsIsSet() const;
  void unsetOperations();
  /// <summary>
  /// Text description of the custom operation
  /// </summary>
  std::string getDescription() const;
  void setDescription(std::string const& value);
  bool descriptionIsSet() const;
  void unsetDescription();

  friend void to_json(nlohmann::json& j, const CustomOperation& o);
  friend void from_json(const nlohmann::json& j, CustomOperation& o);

 protected:
  CommunicationType m_CommType;

  std::string m_CustOpName;

  std::vector<Operation> m_Operations;
  bool m_OperationsIsSet;
  std::string m_Description;
  bool m_DescriptionIsSet;
};

}  // namespace org::openapitools::server::model

#endif /* CustomOperation_H_ */
