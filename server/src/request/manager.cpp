#include <iostream>

#include <rapidjson/document.h>

#include <request/manager.h>
#include <request/models/get.h>
#include <request/models/set.h>

namespace request {

Manager::Manager() = default;
Manager::~Manager() = default;

std::string Manager::Process(std::string const& request_json_as_string) {
    auto prepared_request = Prepare(request_json_as_string);
    if (!prepared_request) {
        return GetErrorResultJSON("Parse request args FAILED");
    }

    auto request_result = prepared_request->Process();
    if (!request_result) {
        return GetErrorResultJSON("Request process FAILED");
    }

    auto request_result_as_json = request_result->ToJson();
    if (!request_result_as_json.HasMember("result")) {
        return GetErrorResultJSON("Parse request result FAILED");
    }

    return request_result_as_json["result"].GetString();
}

std::unique_ptr<IRequest> Manager::Prepare(std::string const& request_json_as_string) {
    rapidjson::Document request_json;
    request_json.Parse(request_json_as_string.c_str());

    if (request_json.HasParseError()) {
        std::cerr << "[SERVER] Parse request FAILED" << std::endl;
        return nullptr;
    }

    if (!request_json.HasMember("method") || !request_json.HasMember("key")) {
        std::cerr << "[SERVER] Invalid request format" << std::endl;
        return nullptr;
    }

    std::string method_name = request_json["method"].GetString();
    std::string key = request_json["key"].GetString();

    if (method_name == "$get") {
        return std::make_unique<models::Get>(key);
    }

    if (method_name == "$set") {
        if (!request_json.HasMember("value")) {
            std::cerr << "[SERVER] Invalid \"$set\"-request format" << std::endl;
            return nullptr;
        }

        std::string new_value = request_json["value"].GetString();
        return std::make_unique<models::Set>(key, new_value);
    }

    std::cerr << "[SERVER] Unknown method \"" + method_name + "\"." << std::endl;
    return nullptr;
}

std::string Manager::GetErrorResultJSON(std::string const& error_message) {
    return R"({
    "error": ")" +
           error_message + "\"\n}";
}

}  // namespace request
