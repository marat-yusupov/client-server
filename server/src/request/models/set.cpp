#include <iostream>
#include <memory>

#include <rapidjson/document.h>

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

std::unique_ptr<IResult> Set::Process() {
    try {
        auto it = MockDataTable.find(mKey);
        if (it == MockDataTable.end()) {
            MockDataTable.emplace(mKey, mNewValue);
            return std::make_unique<SetResult>();
        }

        MockDataTable[mKey] = mNewValue;
        return std::make_unique<SetResult>();
    } catch (...) {
        return std::make_unique<SetResult>(false);
    }
}

}  // namespace request::models