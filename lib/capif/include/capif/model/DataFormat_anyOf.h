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
 * DataFormat_anyOf.h
 *
 *
 */

#ifndef DataFormat_anyOf_H_
#define DataFormat_anyOf_H_

#include <nlohmann/json.hpp>

namespace org::openapitools::server::model {

/// <summary>
///
/// </summary>
class DataFormat_anyOf {
 public:
  DataFormat_anyOf();
  virtual ~DataFormat_anyOf() = default;

  enum class eDataFormat_anyOf {
    // To have a valid default value.
    // Avoiding name clashes with user defined
    // enum values
    INVALID_VALUE_OPENAPI_GENERATED = 0,
    JSON
  };

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

  bool operator==(const DataFormat_anyOf& rhs) const;
  bool operator!=(const DataFormat_anyOf& rhs) const;

  /////////////////////////////////////////////
  /// DataFormat_anyOf members

  DataFormat_anyOf::eDataFormat_anyOf getValue() const;
  void setValue(DataFormat_anyOf::eDataFormat_anyOf value);

  friend void to_json(nlohmann::json& j, const DataFormat_anyOf& o);
  friend void from_json(const nlohmann::json& j, DataFormat_anyOf& o);

 protected:
  DataFormat_anyOf::eDataFormat_anyOf m_value =
      DataFormat_anyOf::eDataFormat_anyOf::INVALID_VALUE_OPENAPI_GENERATED;
};

}  // namespace org::openapitools::server::model

#endif /* DataFormat_anyOf_H_ */
