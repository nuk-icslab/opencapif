#include "util.h"
#include <random>
#include <sstream>

namespace util
{
  bsoncxx::document::value njson2bsoncxx(nlohmann::json njson_obj)
  {
    std::string json_str = njson_obj.dump();
    bsoncxx::document::value bson_obj = bsoncxx::from_json(json_str);
    return bson_obj;
  }
  nlohmann::json bsoncxx2njson(bsoncxx::document::view bson_obj)
  {
    std::string json_str = bsoncxx::to_json(bson_obj);
    nlohmann::json json_obj = nlohmann::json::parse(json_str);
    return json_obj;
  }
  namespace uuid
  {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4()
    {
      std::stringstream ss;
      int i;
      ss << std::hex;
      for (i = 0; i < 8; i++)
      {
        ss << dis(gen);
      }
      ss << "-";
      for (i = 0; i < 4; i++)
      {
        ss << dis(gen);
      }
      ss << "-4";
      for (i = 0; i < 3; i++)
      {
        ss << dis(gen);
      }
      ss << "-";
      ss << dis2(gen);
      for (i = 0; i < 3; i++)
      {
        ss << dis(gen);
      }
      ss << "-";
      for (i = 0; i < 12; i++)
      {
        ss << dis(gen);
      };
      return ss.str();
    }
  }
} // namespace util
