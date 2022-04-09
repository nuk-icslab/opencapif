
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

    const std::string API_ROOT = "http://localhost:8080";

    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_get(const std::string &apfId, Pistache::Http::ResponseWriter &response)
    {
        std::string res;
        res = "Retrieve all published APIs\n";
        res += "apfId=" + apfId + "\n";

        response.send(Pistache::Http::Code::Ok, res);
    }
    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_post(const std::string &apfId, const ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response)
    {
        try
        {
            nlohmann::json res;

            nlohmann::json json_obj;
            to_json(json_obj, serviceAPIDescription);

            spdlog::info("Received an API publishing request:");
            spdlog::info("  apfId={}", apfId);
            spdlog::info("  data={}", json_obj.dump());

            bsoncxx::document::value document = util::njson2bsoncxx(json_obj);

            auto result = api_collection.insert_one(std::move(document));
            std::string api_id = result->inserted_id().get_oid().value.to_string();
            spdlog::info("New API inserted to database. apiId={}", api_id);

            std::string new_resource_locaiton = fmt::format(
                "{}/published-apis/v1/{}/service-apis/{}", API_ROOT, apfId, api_id);

            res["apiName"] = serviceAPIDescription.getApiName();
            res["apiId"] = api_id;

            response.headers()
                .add<Pistache::Http::Header::Location>(new_resource_locaiton)
                .add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
            response.send(Pistache::Http::Code::Ok, res.dump());
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When inserting to database: {}", e.what());
            spdlog::error("No new API will be inserted.");
            response.send(Pistache::Http::Code::Internal_Server_Error,
                          "{'status':500}");
        }
    }
    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_service_api_id_delete(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response)
    {
        spdlog::info("Received an API unpublishing request:");
        spdlog::info("  apfId={}", apfId);
        spdlog::info("  serviceApiId={}", serviceApiId);

        // [TODO] Implementation of API unpublishing

        response.send(Pistache::Http::Code::Service_Unavailable);
    }
    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_service_api_id_get(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response)
    {
        try
        {
            spdlog::info("Received an API retrieving request:");
            spdlog::info("  apfId={}", apfId);
            spdlog::info("  serviceApiId={}", serviceApiId);

            bsoncxx::oid oid{bsoncxx::stdx::string_view{serviceApiId}};
            bsoncxx::stdx::optional<bsoncxx::document::value> result =
                api_collection.find_one(bsoncxx::builder::stream::document{}
                                        << "_id" << oid
                                        << bsoncxx::builder::stream::finalize);
            if (result)
            {
                response.send(Pistache::Http::Code::Ok, bsoncxx::to_json(*result));
            }
            else
            {
                response.send(Pistache::Http::Code::Not_Found, "{'status':404}");
            }
        }
        catch (bsoncxx::exception &e)
        {
            spdlog::error("When parsing API id: {}", e.what());
            response.send(Pistache::Http::Code::Not_Found, "{'status':404}");
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When inserting to database: {}", e.what());
            response.send(Pistache::Http::Code::Internal_Server_Error,
                          "{'status':500}");
        }
    }
    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_service_api_id_put(const std::string &serviceApiId, const std::string &apfId, const ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response)
    {
        nlohmann::json json_obj;
        to_json(json_obj, serviceAPIDescription);
        spdlog::info("Received an API updating request:");
        spdlog::info("  apfId={}", apfId);
        spdlog::info("  serviceApiId={}", serviceApiId);
        spdlog::info("  data={}", json_obj.dump());

        // [TODO] Implementation of API updating

        response.send(Pistache::Http::Code::Service_Unavailable);
    }
}