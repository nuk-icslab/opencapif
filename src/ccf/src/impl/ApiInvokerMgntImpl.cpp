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
    void DefaultApiImpl::api_invoker_management_v1_onboarded_invokers_onboarding_id_delete(const std::string &onboardingId, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::api_invoker_management_v1_onboarded_invokers_onboarding_id_put(const std::string &onboardingId, const APIInvokerEnrolmentDetails &aPIInvokerEnrolmentDetails, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
    void DefaultApiImpl::api_invoker_management_v1_onboarded_invokers_post(const APIInvokerEnrolmentDetails &aPIInvokerEnrolmentDetails, Pistache::Http::ResponseWriter &response)
    {
        response.send(Pistache::Http::Code::Not_Implemented, "Not Implemented\n");
    }
}