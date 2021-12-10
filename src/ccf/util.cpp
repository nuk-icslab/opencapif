#include "util.h"

namespace util {
bsoncxx::document::value njson2bsoncxx(nlohmann::json njson_obj) {
  std::string json_str = njson_obj.dump();
  bsoncxx::document::value bson_obj = bsoncxx::from_json(json_str);
  return bson_obj;
}
nlohmann::json bsoncxx2njson(bsoncxx::document::view bson_obj) {
  std::string json_str = bsoncxx::to_json(bson_obj);
  nlohmann::json json_obj = nlohmann::json::parse(json_str);
  return json_obj;
}
}  // namespace util