#include <iostream>
#include <memory>

#include <rapidjson/document.h>

#include <request/models/get.h>

namespace request::models {

GetResult::GetResult() = default;

GetResult::~GetResult() = default;

rapidjson::Document GetResult::ToJson() {
    return rapidjson::Document();
}

Get::Get(std::string const& key) {}

Get::~Get() {}

std::unique_ptr<IResult> Get::Process() {
    return nullptr;
}

}  // namespace request::models
