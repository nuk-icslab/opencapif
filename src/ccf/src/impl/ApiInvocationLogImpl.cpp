#include "DefaultApiImpl.h"
#include "util.h"
#include "config.h"
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
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        try
        {
            nlohmann::json json;
            std::string log_id, new_resource_location;

            json["aefId"] = aefId;
            json["apiInvokerId"] = invocationLog.getApiInvokerId();
            json["apiId"] = invocationLog.getLogs()[0].getApiId();
            json["apiName"] = invocationLog.getLogs()[0].getApiName();
            json["apiVersion"] = invocationLog.getLogs()[0].getApiVersion();
            json["resourceName"] = invocationLog.getLogs()[0].getResourceName();
            json["protocol"] = invocationLog.getLogs()[0].getProtocol();
            json["operation"] = invocationLog.getLogs()[0].getOperation();
            json["result"] = invocationLog.getLogs()[0].getResult();
            json["invocationTime"] = invocationLog.getLogs()[0].getInvocationTime();

            spdlog::info("Received an invocation log request:");
            spdlog::info("  aefId={}", aefId);
            spdlog::info("  data={}", json.dump());

            bsoncxx::document::value document = util::njson2bsoncxx(json);
            auto result = log_collection.insert_one(std::move(document));
            log_id = result->inserted_id().get_oid().value.to_string();
            spdlog::info("New log inserted to database. logId={}", log_id);

            new_resource_location = fmt::format(
                "{}/api-invocation-logs/v1/{}/logs/{}", config::API_ROOT, aefId, log_id);

            to_json(json, invocationLog);

            response.headers().add<Pistache::Http::Header::Location>(new_resource_location);
            response.send(Pistache::Http::Code::Created, json.dump());
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When inserting to database: {}", e.what());
            spdlog::error("No new log will be inserted.");
            response.send(Pistache::Http::Code::Internal_Server_Error, "{'status':500}");
        }
    }
}