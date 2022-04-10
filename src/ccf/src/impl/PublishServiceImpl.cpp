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
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        nlohmann::json res_json = nlohmann::json::array();

        mongocxx::cursor api_cursor = api_collection.find(
            bsoncxx::builder::stream::document{} << "apfId" << apfId << bsoncxx::builder::stream::finalize);
        for (auto api_doc : api_cursor)
        {
            ServiceAPIDescription api;

            nlohmann::json json = util::bsoncxx2njson(api_doc);

            from_json(json, api);
            api.setApiId(api_doc["_id"].get_oid().value.to_string());
            to_json(json, api);

            res_json.push_back(json);
        }

        // to_json(res_json, res);
        response.send(Pistache::Http::Code::Ok, res_json.dump());
    }

    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_post(const std::string &apfId, const ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response)
    {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        try
        {
            ServiceAPIDescription res;
            nlohmann::json json;
            std::string api_id, new_resource_location;

            to_json(json, serviceAPIDescription);

            spdlog::info("Received an API publishing request:");
            spdlog::info("  apfId={}", apfId);
            spdlog::info("  data={}", json.dump());

            json["apfId"] = apfId;
            bsoncxx::document::value document = util::njson2bsoncxx(json);
            auto result = api_collection.insert_one(std::move(document));
            api_id = result->inserted_id().get_oid().value.to_string();
            spdlog::info("New API inserted to database. apiId={}", api_id);

            res.setApiName(serviceAPIDescription.getApiName());
            res.setApiId(api_id);
            new_resource_location = fmt::format(
                "{}/published-apis/v1/{}/service-apis/{}", API_ROOT, apfId, api_id);

            to_json(json, res);

            response.headers().add<Pistache::Http::Header::Location>(new_resource_location);
            response.send(Pistache::Http::Code::Ok, json.dump());
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When inserting to database: {}", e.what());
            spdlog::error("No new API will be inserted.");
            response.send(Pistache::Http::Code::Internal_Server_Error, "{'status':500}");
        }
    }
    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_service_api_id_delete(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response)
    {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        spdlog::info("Received an API unpublishing request:");
        spdlog::info("  apfId={}", apfId);
        spdlog::info("  serviceApiId={}", serviceApiId);

        // [TODO] Implementation of API unpublishing

        response.send(Pistache::Http::Code::Not_Implemented);
    }

    void DefaultApiImpl::published_apis_v1_apf_id_service_apis_service_api_id_get(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response)
    {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
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
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        nlohmann::json json_obj;
        to_json(json_obj, serviceAPIDescription);
        spdlog::info("Received an API updating request:");
        spdlog::info("  apfId={}", apfId);
        spdlog::info("  serviceApiId={}", serviceApiId);
        spdlog::info("  data={}", json_obj.dump());

        // [TODO] Implementation of API updating

        response.send(Pistache::Http::Code::Not_Implemented);
    }
}