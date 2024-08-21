#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <data/config_handler.h>
#include <request/models/set.h>

namespace request::models {

SetResult::SetResult(bool is_success) : mIsSuccess{is_success} {}

SetResult::~SetResult() = default;

rapidjson::Document SetResult::ToJson() {
    rapidjson::Document json;
    json.SetObject();
    json.AddMember("result", mIsSuccess, json.GetAllocator());
    return json;
}

Set::Set(std::string const& key, std::string const& new_value) : mKey{key}, mNewValue{new_value} {}

Set::~Set() {}

RequestName Set::Name() {
    return RequestName::Set;
}

std::unique_ptr<IResult> Set::Process() {
    auto& config_handler = data::ConfigHandler::Instance();
    auto result = config_handler.Write(mKey, mNewValue);

    return std::make_unique<SetResult>(result);
}

}  // namespace request::models