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
    void DefaultApiImpl::logs_v1_api_invocation_logs_get(const std::optional<std::string> &aefId, const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &timeRangeStart, const std::optional<std::string> &timeRangeEnd, const std::optional<std::string> &apiId, const std::optional<std::string> &apiName, const std::optional<std::string> &apiVersion, const std::optional<Protocol> &protocol, const std::optional<Operation> &operation, const std::optional<std::string> &result, const std::optional<std::string> &resourceName, const std::optional<InterfaceDescription> &srcInterface, const std::optional<InterfaceDescription> &destInterface, const std::optional<std::string> &supportedFeatures, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
}