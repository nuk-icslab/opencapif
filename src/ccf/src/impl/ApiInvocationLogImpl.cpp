
/**
 * Merged 3GPP CAPIF API
 * No description provided (generated by Openapi Generator https://github.com/openapitools/openapi-generator)
 *
 * The version of the OpenAPI document: h20
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */

#include "DefaultApiImpl.h"
#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <bsoncxx/json.hpp>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <nlohmann/json.hpp>

namespace org::openapitools::server::api
{

    using namespace org::openapitools::server::model;
    void DefaultApiImpl::api_invocation_logs_v1_aef_id_logs_post(const std::string &aefId, const InvocationLog &invocationLog, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Ok, "Do some magic\n");
    }
}