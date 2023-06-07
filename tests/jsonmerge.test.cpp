#include "jsonCCL/jsonCCL.hpp"

#include <catch2/catch_test_macros.hpp>

#include <nlohmann/json.hpp>

#include "iostream"


using json = nlohmann::json;
using namespace nlohmann::literals;

using namespace std;

TEST_CASE("Merge Operation", "[core]") {
  json target = R"({
                "key1": "v1", "key2": "a","key3": "c"
            })"_json;

  json patch = R"({
       "key1": "v3"
    })"_json;

  json result = jsonCCL::jsonmerge(target,patch);
  json expected = {{"key1", "v3"}, {"key2", "a"},{"key3", "c"}};

  REQUIRE(result == expected);
}

TEST_CASE("Get Path", "[core]") {
  std::string expected = "/Users/yigitcanozkaya/Desktop/492project/CMPE492PROJECT/";
  jsonCCL::setPath("/Users/yigitcanozkaya/Desktop/492project/CMPE492PROJECT/");
  std::string result = jsonCCL::getPath();
  REQUIRE(result == expected);
}

TEST_CASE("Read and Get Json", "[core]") {
  jsonCCL::setPath("/Users/yigitcanozkaya/Desktop/492project/CMPE492PROJECT/");
  jsonCCL::readJson("deneme.json");
  json expected = R"({
    "age": 30,
    "car": {
        "araba1": {
            "araba5": "mercedes"
        },
        "araba2": "bmw"
    },
    "name": 3122
})"_json;
  json result = jsonCCL::getJson();
  REQUIRE(result == expected);
}

TEST_CASE("Parse Merge Json", "[core]") {
  jsonCCL::setPath("/Users/yigitcanozkaya/Desktop/492project/CMPE492PROJECT/");
  jsonCCL::readJson("deneme.json");
  nlohmann::json expected = R"({
            "araba5": "mercedes"
        })"_json;
  jsonCCL::setValue("car" , {{"araba1",{{"araba5","mercedes"}}}, {"araba2","bmw"}});
  nlohmann::json result = jsonCCL::getValue("araba1");
  REQUIRE(result == expected);
}

// Complete the test suite by writing more tests...
// When is it a good time to stop writing more tests?