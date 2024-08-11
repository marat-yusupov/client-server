#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <request/models/set.h>

namespace request::models {

SetResult::SetResult() = default;

SetResult::~SetResult() = default;

rapidjson::Document SetResult::ToJson() {
    return rapidjson::Document();
}

Set::Set(std::string const& key, std::string const& new_value) {}

Set::~Set() {}

std::unique_ptr<IResult> Set::Process() {
    return nullptr;
}

}  // namespace request::models