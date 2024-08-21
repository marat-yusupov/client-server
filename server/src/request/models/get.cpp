#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <data/config_handler.h>
#include <request/models/get.h>

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
    auto& config_handler = data::ConfigHandler::Instance();
    auto result = config_handler.Read(mKey);

    return std::make_unique<GetResult>(result);
}

}  // namespace request::models
