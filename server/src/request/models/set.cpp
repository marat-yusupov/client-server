#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <data/config.h>
#include <request/models/set.h>

// TODO: dell
#include <request/mock_data_table.h>

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
    auto& config = data::Config::Instance();
    auto result = config.Write(mKey, mNewValue);

    return std::make_unique<SetResult>(result);
}

}  // namespace request::models