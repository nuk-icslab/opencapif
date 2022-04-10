#include "DefaultApiImpl.h"
#include "util.h"
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
    void DefaultApiImpl::service_apis_v1_all_service_apis_get(const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &apiName, const std::optional<std::string> &apiVersion, const std::optional<CommunicationType> &commType, const std::optional<Protocol> &protocol, const std::optional<std::string> &aefId, const std::optional<DataFormat> &dataFormat, const std::optional<std::string> &apiCat, const std::optional<AefLocation> &preferredAefLoc, const std::optional<std::string> &supportedFeatures, const std::optional<std::string> &apiSupportedFeatures, Pistache::Http::ResponseWriter &response)
    {
        // Allow CORS
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        try
        {
            spdlog::info("Received service API discover request form API invoker {}",
                         apiInvokerId.value());

            nlohmann::json res;

            /*
             * [TODO] Query using restrict conditions
             */

            std::vector<nlohmann::json> result;
            bsoncxx::document::view_or_value filter;
            if (apiName)
            {
                filter = bsoncxx::builder::stream::document{} << "apiName" << apiName.value() << bsoncxx::builder::stream::finalize;
            }
            mongocxx::cursor api_cursor = api_collection.find(filter);

            for (auto api_doc : api_cursor)
            {
                ServiceAPIDescription api;

                nlohmann::json json_obj = util::bsoncxx2njson(api_doc);

                from_json(json_obj, api);
                api.setApiId(api_doc["_id"].get_oid().value.to_string());
                to_json(json_obj, api);

                result.push_back(json_obj);
            }

            res["serviceAPIDescriptions"] = result;
            response.send(Pistache::Http::Code::Ok, res.dump());
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When quering database: {}", e.what());
            response.send(Pistache::Http::Code::Internal_Server_Error,
                          "{'status':500}");
        }
    }
}