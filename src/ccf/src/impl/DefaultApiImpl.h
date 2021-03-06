/*
 * DefaultApiImpl.h
 *
 *
 */

#ifndef DEFAULT_API_IMPL_H_
#define DEFAULT_API_IMPL_H_

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <memory>
#include <optional>

#include <DefaultApi.h>

#include <fmt/core.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <spdlog/spdlog.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/exception/exception.hpp>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <nlohmann/json.hpp>
#include <string>

#include "APIInvokerEnrolmentDetails.h"
#include "APIProviderEnrolmentDetails.h"
#include "AccessTokenErr.h"
#include "AccessTokenRsp.h"
#include "CommunicationType.h"
#include "DataFormat.h"
#include "DiscoveredAPIs.h"
#include "InvocationLog.h"
#include "ProblemDetails.h"
#include "Protocol.h"
#include "SecurityNotification.h"
#include "ServiceAPIDescription.h"
#include "ServiceSecurity.h"
#include <string>

namespace org::openapitools::server::api
{

    using namespace org::openapitools::server::model;

    class DefaultApiImpl : public org::openapitools::server::api::DefaultApi
    {
    public:
        explicit DefaultApiImpl(const std::shared_ptr<Pistache::Rest::Router> &rtr,
                                const std::shared_ptr<mongocxx::database> &database);
        ~DefaultApiImpl() override = default;

        void access_control_policy_v1_access_control_policy_list_service_api_id_get(const std::string &serviceApiId, const std::optional<std::string> &aefId, const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &supportedFeatures, Pistache::Http::ResponseWriter &response);
        void api_invocation_logs_v1_aef_id_logs_post(const std::string &aefId, const InvocationLog &invocationLog, Pistache::Http::ResponseWriter &response);
        void api_invoker_management_v1_onboarded_invokers_onboarding_id_delete(const std::string &onboardingId, Pistache::Http::ResponseWriter &response);
        void api_invoker_management_v1_onboarded_invokers_onboarding_id_put(const std::string &onboardingId, const APIInvokerEnrolmentDetails &aPIInvokerEnrolmentDetails, Pistache::Http::ResponseWriter &response);
        void api_invoker_management_v1_onboarded_invokers_post(const APIInvokerEnrolmentDetails &aPIInvokerEnrolmentDetails, Pistache::Http::ResponseWriter &response);
        void api_provider_management_v1_registrations_post(const APIProviderEnrolmentDetails &aPIProviderEnrolmentDetails, Pistache::Http::ResponseWriter &response);
        void api_provider_management_v1_registrations_registration_id_delete(const std::string &registrationId, Pistache::Http::ResponseWriter &response);
        void api_provider_management_v1_registrations_registration_id_put(const std::string &registrationId, const APIProviderEnrolmentDetails &aPIProviderEnrolmentDetails, Pistache::Http::ResponseWriter &response);
        void capif_events_v1_subscriber_id_subscriptions_post(const std::string &subscriberId, const EventSubscription &eventSubscription, Pistache::Http::ResponseWriter &response);
        void capif_events_v1_subscriber_id_subscriptions_subscription_id_delete(const std::string &subscriberId, const std::string &subscriptionId, Pistache::Http::ResponseWriter &response);
        void capif_routing_info_v1_service_apis_service_api_id_get(const std::string &serviceApiId, const std::optional<std::string> &aefId, const std::optional<std::string> &suppFeat, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_securities_security_id_token_post(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_trusted_invokers_api_invoker_id_delete(const std::string &apiInvokerId, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_trusted_invokers_api_invoker_id_delete_post(const std::string &apiInvokerId, const SecurityNotification &securityNotification, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_trusted_invokers_api_invoker_id_get(const std::string &apiInvokerId, const std::optional<bool> &authenticationInfo, const std::optional<bool> &authorizationInfo, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_trusted_invokers_api_invoker_id_put(const std::string &apiInvokerId, const ServiceSecurity &serviceSecurity, Pistache::Http::ResponseWriter &response);
        void capif_security_v1_trusted_invokers_api_invoker_id_update_post(const std::string &apiInvokerId, const ServiceSecurity &serviceSecurity, Pistache::Http::ResponseWriter &response);
        void logs_v1_api_invocation_logs_get(const std::optional<std::string> &aefId, const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &timeRangeStart, const std::optional<std::string> &timeRangeEnd, const std::optional<std::string> &apiId, const std::optional<std::string> &apiName, const std::optional<std::string> &apiVersion, const std::optional<Protocol> &protocol, const std::optional<Operation> &operation, const std::optional<std::string> &result, const std::optional<std::string> &resourceName, const std::optional<InterfaceDescription> &srcInterface, const std::optional<InterfaceDescription> &destInterface, const std::optional<std::string> &supportedFeatures, Pistache::Http::ResponseWriter &response);
        void published_apis_v1_apf_id_service_apis_get(const std::string &apfId, Pistache::Http::ResponseWriter &response);
        void published_apis_v1_apf_id_service_apis_post(const std::string &apfId, const ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response);
        void published_apis_v1_apf_id_service_apis_service_api_id_delete(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response);
        void published_apis_v1_apf_id_service_apis_service_api_id_get(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response);
        void published_apis_v1_apf_id_service_apis_service_api_id_put(const std::string &serviceApiId, const std::string &apfId, const ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response);
        void service_apis_v1_all_service_apis_get(const std::optional<std::string> &apiInvokerId, const std::optional<std::string> &apiName, const std::optional<std::string> &apiVersion, const std::optional<CommunicationType> &commType, const std::optional<Protocol> &protocol, const std::optional<std::string> &aefId, const std::optional<DataFormat> &dataFormat, const std::optional<std::string> &apiCat, const std::optional<AefLocation> &preferredAefLoc, const std::optional<std::string> &supportedFeatures, const std::optional<std::string> &apiSupportedFeatures, Pistache::Http::ResponseWriter &response);

    private:
        std::shared_ptr<mongocxx::database> db;
        mongocxx::collection api_collection;
        mongocxx::collection log_collection;
    };

} // namespace org::openapitools::server::api

#endif
