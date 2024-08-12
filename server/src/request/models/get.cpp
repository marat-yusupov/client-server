#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <request/models/get.h>

// TODO: dell
#include <request/mock_data_table.h>

namespace request::models {

GetResult::GetResult(std::string const& value) : mValue{value} {}

GetResult::~GetResult() = default;

rapidjson::Document GetResult::ToJson() {
    rapidjson::Document json;
    json.SetObject();
    rapidjson::Value value(mValue.c_str(), json.GetAllocator());
    json.AddMember("result", value, json.GetAllocator());
    return json;
}

Get::Get(std::string const& key) : mKey{key} {}
Get::~Get() {}

RequestName Get::Name() {
    return RequestName::Get;
}

std::unique_ptr<IResult> Get::Process() {
    auto it = MockDataTable.find(mKey);
    if (it == MockDataTable.end()) {
        return nullptr;
    }

    auto value = it->second;
    if (value.empty()) {
        return nullptr;
    }

    return std::make_unique<GetResult>(value);
}

}  // namespace request::models
