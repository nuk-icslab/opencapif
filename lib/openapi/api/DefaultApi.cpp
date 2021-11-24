/**
 * CAPIF_Publish_Service_API
 * API for publishing service APIs. © 2021, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.0-alpha.2
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "DefaultApi.h"

#include "Helpers.h"

namespace org::openapitools::server::api {

using namespace org::openapitools::server::helpers;
using namespace org::openapitools::server::model;

const std::string DefaultApi::base = "/published-apis/v1";

DefaultApi::DefaultApi(const std::shared_ptr<Pistache::Rest::Router> &rtr)
    : router(rtr) {}

void DefaultApi::init() { setupRoutes(); }

void DefaultApi::setupRoutes() {
  using namespace Pistache::Rest;

  Routes::Get(*router, base + "/:apfId/service-apis",
              Routes::bind(&DefaultApi::apf_id_service_apis_get_handler, this));
  Routes::Post(
      *router, base + "/:apfId/service-apis",
      Routes::bind(&DefaultApi::apf_id_service_apis_post_handler, this));
  Routes::Delete(
      *router, base + "/:apfId/service-apis/:serviceApiId",
      Routes::bind(
          &DefaultApi::apf_id_service_apis_service_api_id_delete_handler,
          this));
  Routes::Get(
      *router, base + "/:apfId/service-apis/:serviceApiId",
      Routes::bind(&DefaultApi::apf_id_service_apis_service_api_id_get_handler,
                   this));
  Routes::Put(
      *router, base + "/:apfId/service-apis/:serviceApiId",
      Routes::bind(&DefaultApi::apf_id_service_apis_service_api_id_put_handler,
                   this));

  // Default handler, called when a route is not found
  router->addCustomHandler(
      Routes::bind(&DefaultApi::default_api_default_handler, this));
}

std::pair<Pistache::Http::Code, std::string> DefaultApi::handleParsingException(
    const std::exception &ex) const noexcept {
  try {
    throw;
  } catch (nlohmann::detail::exception &e) {
    return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());
  } catch (org::openapitools::server::helpers::ValidationException &e) {
    return std::make_pair(Pistache::Http::Code::Bad_Request, e.what());
  } catch (std::exception &e) {
    return std::make_pair(Pistache::Http::Code::Internal_Server_Error,
                          e.what());
  }
}

std::pair<Pistache::Http::Code, std::string>
DefaultApi::handleOperationException(const std::exception &ex) const noexcept {
  return std::make_pair(Pistache::Http::Code::Internal_Server_Error, ex.what());
}

void DefaultApi::apf_id_service_apis_get_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  try {
    // Getting the path params
    auto apfId = request.param(":apfId").as<std::string>();

    try {
      this->apf_id_service_apis_get(apfId, response);
    } catch (Pistache::Http::HttpError &e) {
      response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
      return;
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleOperationException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

  } catch (std::exception &e) {
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
  }
}
void DefaultApi::apf_id_service_apis_post_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  try {
    // Getting the path params
    auto apfId = request.param(":apfId").as<std::string>();

    // Getting the body param

    ServiceAPIDescription serviceAPIDescription;

    try {
      nlohmann::json::parse(request.body()).get_to(serviceAPIDescription);
      serviceAPIDescription.validate();
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleParsingException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

    try {
      this->apf_id_service_apis_post(apfId, serviceAPIDescription, response);
    } catch (Pistache::Http::HttpError &e) {
      response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
      return;
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleOperationException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

  } catch (std::exception &e) {
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
  }
}
void DefaultApi::apf_id_service_apis_service_api_id_delete_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  try {
    // Getting the path params
    auto serviceApiId = request.param(":serviceApiId").as<std::string>();
    auto apfId = request.param(":apfId").as<std::string>();

    try {
      this->apf_id_service_apis_service_api_id_delete(serviceApiId, apfId,
                                                      response);
    } catch (Pistache::Http::HttpError &e) {
      response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
      return;
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleOperationException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

  } catch (std::exception &e) {
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
  }
}
void DefaultApi::apf_id_service_apis_service_api_id_get_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  try {
    // Getting the path params
    auto serviceApiId = request.param(":serviceApiId").as<std::string>();
    auto apfId = request.param(":apfId").as<std::string>();

    try {
      this->apf_id_service_apis_service_api_id_get(serviceApiId, apfId,
                                                   response);
    } catch (Pistache::Http::HttpError &e) {
      response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
      return;
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleOperationException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

  } catch (std::exception &e) {
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
  }
}
void DefaultApi::apf_id_service_apis_service_api_id_put_handler(
    const Pistache::Rest::Request &request,
    Pistache::Http::ResponseWriter response) {
  try {
    // Getting the path params
    auto serviceApiId = request.param(":serviceApiId").as<std::string>();
    auto apfId = request.param(":apfId").as<std::string>();

    // Getting the body param

    ServiceAPIDescription serviceAPIDescription;

    try {
      nlohmann::json::parse(request.body()).get_to(serviceAPIDescription);
      serviceAPIDescription.validate();
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleParsingException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

    try {
      this->apf_id_service_apis_service_api_id_put(
          serviceApiId, apfId, serviceAPIDescription, response);
    } catch (Pistache::Http::HttpError &e) {
      response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
      return;
    } catch (std::exception &e) {
      const std::pair<Pistache::Http::Code, std::string> errorInfo =
          this->handleOperationException(e);
      response.send(errorInfo.first, errorInfo.second);
      return;
    }

  } catch (std::exception &e) {
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
  }
}

void DefaultApi::default_api_default_handler(
    const Pistache::Rest::Request &, Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Not_Found,
                "The requested method does not exist");
}

}  // namespace org::openapitools::server::api
