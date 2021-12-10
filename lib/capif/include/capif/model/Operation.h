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
 * Operation.h
 *
 * Possible values are - GET: HTTP GET method - POST: HTTP POST method - PUT:
 * HTTP PUT method - PATCH: HTTP PATCH method - DELETE: HTTP DELETE method
 */

#ifndef Operation_H_
#define Operation_H_

#include <nlohmann/json.hpp>

#include "capif/model/Operation_anyOf.h"

namespace org::openapitools::server::model {

/// <summary>
/// Possible values are - GET: HTTP GET method - POST: HTTP POST method - PUT:
/// HTTP PUT method - PATCH: HTTP PATCH method - DELETE: HTTP DELETE method
/// </summary>
class Operation {
 public:
  Operation();
  virtual ~Operation() = default;

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

  bool operator==(const Operation& rhs) const;
  bool operator!=(const Operation& rhs) const;

  /////////////////////////////////////////////
  /// Operation members

  Operation_anyOf getValue() const;
  void setValue(Operation_anyOf value);
  Operation_anyOf::eOperation_anyOf getEnumValue() const;
  void setEnumValue(Operation_anyOf::eOperation_anyOf value);
  friend void to_json(nlohmann::json& j, const Operation& o);
  friend void from_json(const nlohmann::json& j, Operation& o);
  friend void to_json(nlohmann::json& j, const Operation_anyOf& o);
  friend void from_json(const nlohmann::json& j, Operation_anyOf& o);

 protected:
  Operation_anyOf m_value;
};

}  // namespace org::openapitools::server::model

#endif /* Operation_H_ */
