#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <request/manager.h>
#include <request/models/get.h>
#include <request/models/set.h>

namespace request {

Manager::Manager() = default;
Manager::~Manager() = default;

std::string Manager::Process(std::string const& request_json_as_string) {
    auto prepared_request = Prepare(request_json_as_string);
    if (!prepared_request) {
        return GetErrorResult("Parse request args FAILED");
    }

    auto request_result = prepared_request->Process();
    if (!request_result) {
        return GetErrorResult("Request process FAILED");
    }

    auto request_result_json = request_result->ToJson();

    rapidjson::StringBuffer sbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sbuf);
    request_result_json.Accept(writer);

    return sbuf.GetString();
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

std::string Manager::GetErrorResult(std::string const& error_message) {
    return "{\"error\":\"" + error_message + "\"}";
}

}  // namespace request
