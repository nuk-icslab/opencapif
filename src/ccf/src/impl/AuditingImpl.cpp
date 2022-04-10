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
    void DefaultApiImpl::logs_v1_api_invocation_logs_get(const std::optional<std::string> &aefId, const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &timeRangeStart, const std::optional<std::string> &timeRangeEnd, const std::optional<std::string> &apiId, const std::optional<std::string> &apiName, const std::optional<std::string> &apiVersion, const std::optional<Protocol> &protocol, const std::optional<Operation> &operation, const std::optional<std::string> &result, const std::optional<std::string> &resourceName, const std::optional<InterfaceDescription> &srcInterface, const std::optional<InterfaceDescription> &destInterface, const std::optional<std::string> &supportedFeatures, Pistache::Http::ResponseWriter &response)
    {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        try
        {
            spdlog::info("Received service log auditing request");
            if (aefId)
            {
                spdlog::info("  AEF: {}", aefId.value());
            }
            if (apiInvokerId)
            {
                spdlog::info("  API invoker: {}", apiInvokerId.value());
            }

            InvocationLog res;
            std::vector<Log> logs;
            nlohmann::json res_json;

            std::vector<nlohmann::json> result;
            nlohmann::json json_filter = nlohmann::json({});
            if (aefId)
            {
                json_filter["aefId"] = aefId.value();
            }
            if (apiInvokerId)
            {
                json_filter["apiInvokerId"] = apiInvokerId.value();
            }
            bsoncxx::document::view_or_value filter = util::njson2bsoncxx(json_filter);

            // spdlog::info("{}", json_filter.dump());

            mongocxx::cursor log_cursor = log_collection.find(filter);

            for (auto log_doc : log_cursor)
            {
                Log log;

                nlohmann::json json_obj = util::bsoncxx2njson(log_doc);
                // spdlog::info("{}", json_obj.dump());
                from_json(json_obj, log);

                logs.push_back(log);
            }

            if (aefId)
            {
                res.setAefId(aefId.value());
            }
            if (apiInvokerId)
            {
                res.setApiInvokerId(apiInvokerId.value());
            }
            res.setLogs(logs);

            to_json(res_json, res);

            response.send(Pistache::Http::Code::Ok, res_json.dump());
        }
        catch (mongocxx::exception &e)
        {
            spdlog::error("When quering database: {}", e.what());
            response.send(Pistache::Http::Code::Internal_Server_Error,
                          "{'status':500}");
        }
    }
}