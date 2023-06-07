#include <nlohmann/json.hpp>

#include "iostream"

namespace jsonCCL {

// A dummy function to try before jsonmerge
auto add_two_integer(int a, int b) -> int;

auto jsonmerge(
  nlohmann::json const& target, nlohmann::json const& patch)
  -> nlohmann::json;

auto getPath() -> std::string;

void setPath(std::filesystem::path const& path);

void readJson(std::string const& filename);

auto getJson() -> nlohmann::json;

auto getValue(std::string const& key) -> nlohmann::json;

void setValue(std::string const& key, nlohmann::json const& value );

// Extend the interface to handle by JSON files from the filesystem  
// Check data folder for some example files - you can use std::filesystem

}  // namespace bouncmpe