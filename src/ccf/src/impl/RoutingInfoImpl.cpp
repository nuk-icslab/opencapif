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
    void DefaultApiImpl::capif_routing_info_v1_service_apis_service_api_id_get(const std::string &serviceApiId, const std::optional<std::string> &aefId, const std::optional<std::string> &suppFeat, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
}