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

#include "capif/model/CustomOperation.h"

#include <sstream>

#include "capif/model/Helpers.h"

namespace org::openapitools::server::model {

CustomOperation::CustomOperation() {
  m_CustOpName = "";
  m_OperationsIsSet = false;
  m_Description = "";
  m_DescriptionIsSet = false;
}

void CustomOperation::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw org::openapitools::server::helpers::ValidationException(msg.str());
  }
}

bool CustomOperation::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool CustomOperation::validate(std::stringstream& msg,
                               const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "CustomOperation" : pathPrefix;

  if (operationsIsSet()) {
    const std::vector<Operation>& value = m_Operations;
    const std::string currentValuePath = _pathPrefix + ".operations";

    if (value.size() < 1) {
      success = false;
      msg << currentValuePath << ": must have at least 1 elements;";
    }
    {  // Recursive validation of array elements
      const std::string oldValuePath = currentValuePath;
      int i = 0;
      for (const Operation& value : value) {
        const std::string currentValuePath =
            oldValuePath + "[" + std::to_string(i) + "]";

        success =
            value.validate(msg, currentValuePath + ".operations") && success;

        i++;
      }
    }
  }

  return success;
}

bool CustomOperation::operator==(const CustomOperation& rhs) const {
  return

      (getCommType() == rhs.getCommType()) &&

      (getCustOpName() == rhs.getCustOpName()) &&

      ((!operationsIsSet() && !rhs.operationsIsSet()) ||
       (operationsIsSet() && rhs.operationsIsSet() &&
        getOperations() == rhs.getOperations())) &&

      ((!descriptionIsSet() && !rhs.descriptionIsSet()) ||
       (descriptionIsSet() && rhs.descriptionIsSet() &&
        getDescription() == rhs.getDescription()))

          ;
}

bool CustomOperation::operator!=(const CustomOperation& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const CustomOperation& o) {
  j = nlohmann::json();
  j["commType"] = o.m_CommType;
  j["custOpName"] = o.m_CustOpName;
  if (o.operationsIsSet() || !o.m_Operations.empty())
    j["operations"] = o.m_Operations;
  if (o.descriptionIsSet()) j["description"] = o.m_Description;
}

void from_json(const nlohmann::json& j, CustomOperation& o) {
  j.at("commType").get_to(o.m_CommType);
  j.at("custOpName").get_to(o.m_CustOpName);
  if (j.find("operations") != j.end()) {
    j.at("operations").get_to(o.m_Operations);
    o.m_OperationsIsSet = true;
  }
  if (j.find("description") != j.end()) {
    j.at("description").get_to(o.m_Description);
    o.m_DescriptionIsSet = true;
  }
}

CommunicationType CustomOperation::getCommType() const { return m_CommType; }
void CustomOperation::setCommType(CommunicationType const& value) {
  m_CommType = value;
}
std::string CustomOperation::getCustOpName() const { return m_CustOpName; }
void CustomOperation::setCustOpName(std::string const& value) {
  m_CustOpName = value;
}
std::vector<Operation> CustomOperation::getOperations() const {
  return m_Operations;
}
void CustomOperation::setOperations(std::vector<Operation> const& value) {
  m_Operations = value;
  m_OperationsIsSet = true;
}
bool CustomOperation::operationsIsSet() const { return m_OperationsIsSet; }
void CustomOperation::unsetOperations() { m_OperationsIsSet = false; }
std::string CustomOperation::getDescription() const { return m_Description; }
void CustomOperation::setDescription(std::string const& value) {
  m_Description = value;
  m_DescriptionIsSet = true;
}
bool CustomOperation::descriptionIsSet() const { return m_DescriptionIsSet; }
void CustomOperation::unsetDescription() { m_DescriptionIsSet = false; }

}  // namespace org::openapitools::server::model
