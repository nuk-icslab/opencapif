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

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>
#include <spdlog/spdlog.h>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#ifdef __linux__
#include <signal.h>
#include <unistd.h>

#include <vector>
#endif

#include <pistache/router.h>

#include "DiscoverServiceServerImpl.h"
#include "PublishServiceServerImpl.h"

#define PISTACHE_SERVER_THREADS 2
#define PISTACHE_SERVER_MAX_REQUEST_SIZE 32768
#define PISTACHE_SERVER_MAX_RESPONSE_SIZE 32768

static Pistache::Http::Endpoint *httpEndpoint;
#ifdef __linux__
static void sigHandler [[noreturn]] (int sig) {
  switch (sig) {
    case SIGINT:
    case SIGQUIT:
    case SIGTERM:
    case SIGHUP:
    default:
      httpEndpoint->shutdown();
      break;
  }
  exit(0);
}

static void setUpUnixSignals(std::vector<int> quitSignals) {
  sigset_t blocking_mask;
  sigemptyset(&blocking_mask);
  for (auto sig : quitSignals) sigaddset(&blocking_mask, sig);

  struct sigaction sa;
  sa.sa_handler = sigHandler;
  sa.sa_mask = blocking_mask;
  sa.sa_flags = 0;

  for (auto sig : quitSignals) sigaction(sig, &sa, nullptr);
}
#endif

void api_default_handler(const Pistache::Rest::Request &,
                         Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Not_Found,
                "The requested endpoint does not exist");
}

using namespace org::openapitools::server::api;

int main(int argc, char *argv[]) {
  int port = 8080;
#ifdef __linux__
  std::vector<int> sigs{SIGQUIT, SIGINT, SIGTERM, SIGHUP};
  setUpUnixSignals(sigs);
#endif

  spdlog::info("CAPIF Core Function. version: {}", __CCF_VERSION__);

  /**
   * Initialize connection to MongoDB
   * [TODO] Put parameters into configuration file
   */
  mongocxx::instance inst{};  // This should be done only once.
  mongocxx::client db_conn{mongocxx::uri{"mongodb://localhost:27017"}};
  std::shared_ptr<mongocxx::database> db =
      std::make_shared<mongocxx::database>(db_conn["capif"]);

  Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));

  httpEndpoint = new Pistache::Http::Endpoint((addr));
  auto router = std::make_shared<Pistache::Rest::Router>();

  auto opts =
      Pistache::Http::Endpoint::options().threads(PISTACHE_SERVER_THREADS);
  opts.flags(Pistache::Tcp::Options::ReuseAddr);
  opts.maxRequestSize(PISTACHE_SERVER_MAX_REQUEST_SIZE);
  opts.maxResponseSize(PISTACHE_SERVER_MAX_RESPONSE_SIZE);
  httpEndpoint->init(opts);

  PublishServiceServerImpl PublishServiceServer(router, db);
  PublishServiceServer.init();
  DiscoverServiceServerImpl DiscoverServiceServer(router, db);
  DiscoverServiceServer.init();

  // Default handler, called when a route is not found
  router->addCustomHandler(Pistache::Rest::Routes::bind(&api_default_handler));

  spdlog::info("CAPIF core function is listening on port {}", port);
  httpEndpoint->setHandler(router->handler());
  httpEndpoint->serve();

  httpEndpoint->shutdown();
}
