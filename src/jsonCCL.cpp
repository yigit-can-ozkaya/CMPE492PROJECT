#include "jsonCCL/jsonCCL.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann::literals;

namespace jsonCCL {

static std::filesystem::path jsonPath = "/";

static std::filesystem::path jsonPathwithFileName = "/";

static nlohmann::json currentJson = {};

static nlohmann::json gotValue = NULL;

template<class... Args>
void print(Args... args)
{
    (cout << ... << args) << "\n";
}

void recursive_iterate(nlohmann::json j, std::string const& key)
{
    for(auto [i_key, i_val] : j.items())
    {   
        auto a = i_key;
        auto b = i_val;
        if (i_val.is_structured() && i_key != key)
        {
            recursive_iterate(i_val, key);
        }
        else if(i_key == key){
            gotValue = i_val;
        }
        else
        {
            continue;
        }
    }
}

auto jsonmerge(
  nlohmann::json const& target, nlohmann::json const& patch)
  -> nlohmann::json
{

  // Implement desired functionality here(JSON merge operation)

  nlohmann::json targetd = target;

  targetd.merge_patch(patch);

  return targetd;
}

void setPath(std::filesystem::path const& path) {
  jsonPath = path;
}

auto getPath() -> std::string {
  return jsonPath;
}

void readJson(std::string const& filename) {
  jsonPathwithFileName = jsonPath/filename;
  std::ifstream jsonfile(jsonPathwithFileName);
  currentJson =  nlohmann::json::parse(jsonfile);
  jsonfile.close();
};

auto getJson() -> nlohmann::json {
  return currentJson;
}

auto getValue(std::string const& key) -> nlohmann::json {
  recursive_iterate(currentJson, key);
  return gotValue;
}

void setValue(std::string const& key, nlohmann::json const& value ){
  nlohmann::json jsonValue = value;
  currentJson[key] = jsonValue;
  std::ofstream w_file(jsonPathwithFileName);
  std::string j_string = currentJson.dump(4);
  w_file << j_string <<std::endl;
  w_file.close();
}

}  