#include "DefaultApiImpl.h"

namespace org::openapitools::server::api
{

    using namespace org::openapitools::server::model;

    DefaultApiImpl::DefaultApiImpl(const std::shared_ptr<Pistache::Rest::Router> &rtr,
                                   const std::shared_ptr<mongocxx::database> &database)
        : DefaultApi(rtr), db(database)
    {
        api_collection = (*db)["apis"];
    }

}
