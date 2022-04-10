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
        APIInvokerEnrolmentDetails res;
        nlohmann::json json;
        std::string public_key, invkr_id, new_resource_location;

        public_key = aPIInvokerEnrolmentDetails.getOnboardingInformation().getApiInvokerPublicKey();
        to_json(json, aPIInvokerEnrolmentDetails);

        spdlog::info("Received an Onboarding request:");
        spdlog::info("  data={}", json.dump());

        invkr_id = util::uuid::generate_uuid_v4();

        res.setOnboardingInformation(aPIInvokerEnrolmentDetails.getOnboardingInformation());
        res.setNotificationDestination(aPIInvokerEnrolmentDetails.getNotificationDestination());
        res.setApiInvokerId(invkr_id);
        new_resource_location = fmt::format(
            "{}/api-invoker-management/v1/onboardedInvokers/{}", API_ROOT, invkr_id);

        to_json(json, res);

        response.headers().add<Pistache::Http::Header::Location>(new_resource_location);
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        response.send(Pistache::Http::Code::Created, json.dump());
    }
}