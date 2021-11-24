/**
* CAPIF_Publish_Service_API
* API for publishing service APIs. © 2021, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved. 
*
* The version of the OpenAPI document: 1.2.0-alpha.2
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/
/*
 * DefaultApi.h
 *
 * 
 */

#ifndef DefaultApi_H_
#define DefaultApi_H_


#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/http_headers.h>

#include <utility>

#include "ProblemDetails.h"
#include "ServiceAPIDescription.h"
#include <string>

namespace org::openapitools::server::api
{

class  DefaultApi {
public:
    explicit DefaultApi(const std::shared_ptr<Pistache::Rest::Router>& rtr);
    virtual ~DefaultApi() = default;
    void init();

    static const std::string base;

private:
    void setupRoutes();

    void apf_id_service_apis_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void apf_id_service_apis_post_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void apf_id_service_apis_service_api_id_delete_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void apf_id_service_apis_service_api_id_get_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void apf_id_service_apis_service_api_id_put_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void default_api_default_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

    const std::shared_ptr<Pistache::Rest::Router> router;

    /// <summary>
    /// Helper function to handle unexpected Exceptions during Parameter parsing and validation.
    /// May be overridden to return custom error formats. This is called inside a catch block.
    /// Important: When overriding, do not call `throw ex;`, but instead use `throw;`.
    /// </summary>
    virtual std::pair<Pistache::Http::Code, std::string> handleParsingException(const std::exception& ex) const noexcept;

    /// <summary>
    /// Helper function to handle unexpected Exceptions during processing of the request in handler functions.
    /// May be overridden to return custom error formats. This is called inside a catch block.
    /// Important: When overriding, do not call `throw ex;`, but instead use `throw;`.
    /// </summary>
    virtual std::pair<Pistache::Http::Code, std::string> handleOperationException(const std::exception& ex) const noexcept;

    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Retrieve all published APIs.
    /// </remarks>
    /// <param name="apfId"></param>
    virtual void apf_id_service_apis_get(const std::string &apfId, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Publish a new API.
    /// </remarks>
    /// <param name="apfId"></param>
    /// <param name="serviceAPIDescription"></param>
    virtual void apf_id_service_apis_post(const std::string &apfId, const org::openapitools::server::model::ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Unpublish a published service API.
    /// </remarks>
    /// <param name="serviceApiId"></param>
    /// <param name="apfId"></param>
    virtual void apf_id_service_apis_service_api_id_delete(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Retrieve a published service API.
    /// </remarks>
    /// <param name="serviceApiId"></param>
    /// <param name="apfId"></param>
    virtual void apf_id_service_apis_service_api_id_get(const std::string &serviceApiId, const std::string &apfId, Pistache::Http::ResponseWriter &response) = 0;
    /// <summary>
    /// 
    /// </summary>
    /// <remarks>
    /// Update a published service API.
    /// </remarks>
    /// <param name="serviceApiId"></param>
    /// <param name="apfId"></param>
    /// <param name="serviceAPIDescription"></param>
    virtual void apf_id_service_apis_service_api_id_put(const std::string &serviceApiId, const std::string &apfId, const org::openapitools::server::model::ServiceAPIDescription &serviceAPIDescription, Pistache::Http::ResponseWriter &response) = 0;

};

} // namespace org::openapitools::server::api

#endif /* DefaultApi_H_ */
