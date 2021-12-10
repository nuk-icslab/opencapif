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

#include "DiscoverServiceServerImpl.h"

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <nlohmann/json.hpp>

namespace org {
namespace openapitools {
namespace server {
namespace api {

using namespace org::openapitools::server::model;

DiscoverServiceServerImpl::DiscoverServiceServerImpl(
    const std::shared_ptr<Pistache::Rest::Router> &rtr,
    const std::shared_ptr<mongocxx::database> &database)
    : DiscoverServiceServer(rtr), db(database) {
  api_collection = (*db)["apis"];
}

void DiscoverServiceServerImpl::all_service_apis_get(
    const std::optional<std::string> &apiInvokerId,
    const std::optional<std::string> &apiName,
    const std::optional<std::string> &apiVersion,
    const std::optional<CommunicationType> &commType,
    const std::optional<Protocol> &protocol,
    const std::optional<std::string> &aefId,
    const std::optional<DataFormat> &dataFormat,
    const std::optional<std::string> &apiCat,
    const std::optional<std::string> &supportedFeatures,
    const std::optional<std::string> &apiSupportedFeatures,
    Pistache::Http::ResponseWriter &response) {
  response.send(Pistache::Http::Code::Ok, "Discover service APIs\n");
}

}  // namespace api
}  // namespace server
}  // namespace openapitools
}  // namespace org
