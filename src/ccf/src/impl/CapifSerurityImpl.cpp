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
    void DefaultApiImpl::capif_security_v1_securities_security_id_token_post(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::capif_security_v1_trusted_invokers_api_invoker_id_delete(const std::string &apiInvokerId, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::capif_security_v1_trusted_invokers_api_invoker_id_delete_post(const std::string &apiInvokerId, const SecurityNotification &securityNotification, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::capif_security_v1_trusted_invokers_api_invoker_id_get(const std::string &apiInvokerId, const std::optional<bool> &authenticationInfo, const std::optional<bool> &authorizationInfo, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::capif_security_v1_trusted_invokers_api_invoker_id_put(const std::string &apiInvokerId, const ServiceSecurity &serviceSecurity, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::capif_security_v1_trusted_invokers_api_invoker_id_update_post(const std::string &apiInvokerId, const ServiceSecurity &serviceSecurity, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
}