#ifndef UTIL_H
#define UTIL_H

#include <bsoncxx/json.hpp>
#include <nlohmann/json.hpp>

namespace util
{
    extern bsoncxx::document::value njson2bsoncxx(nlohmann::json njson_obj);
    extern nlohmann::json bsoncxx2njson(bsoncxx::document::view bson_obj);
    namespace uuid
    {
        extern std::string generate_uuid_v4();
    }
} // namespace util
#endif