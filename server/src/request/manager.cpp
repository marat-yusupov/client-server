#include <iostream>
#include <thread>

#include <boost/asio.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <request/manager.h>
#include <request/models/get.h>
#include <request/models/set.h>

namespace request {

Manager::Manager(boost::asio::ip::tcp::socket& socket) : mSocketRef(socket) {}
Manager::~Manager() = default;

void Manager::Process(std::string const& request_json_as_string) {
    auto prepared_request = Prepare(request_json_as_string);
    if (!prepared_request) {
        auto error_responce = GetErrorResult("Parse request args FAILED");
        SendResponce(error_responce);
    }

    auto request_result = prepared_request->Process();
    if (!request_result) {
        auto error_responce = GetErrorResult("Request process FAILED");
        SendResponce(error_responce);
    }

    auto request_result_json = request_result->ToJson();

    rapidjson::StringBuffer sbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sbuf);
    request_result_json.Accept(writer);

    std::string responce = sbuf.GetString();
    SendResponce(responce);
}

std::unique_ptr<IRequest> Manager::Prepare(std::string const& request_json_as_string) {
    rapidjson::Document request_json;
    request_json.Parse(request_json_as_string.c_str());

    if (request_json.HasParseError()) {
        std::cerr << "[SERVER::WARNING] Parse request FAILED" << std::endl;
        return nullptr;
    }

    if (!request_json.HasMember("key") || !request_json.HasMember("method")) {
        std::cerr << "[SERVER::WARNING] Invalid request format" << std::endl;
        return nullptr;
    }

    std::string method_name = request_json["method"].GetString();
    std::string key = request_json["key"].GetString();

    if (method_name == "$get") {
        return std::make_unique<models::Get>(key);
    }

    if (method_name == "$set") {
        if (!request_json.HasMember("value")) {
            std::cerr << "[SERVER::WARNING] Invalid \"$set\"-request format" << std::endl;
            return nullptr;
        }

        std::string new_value = request_json["value"].GetString();
        return std::make_unique<models::Set>(key, new_value);
    }

    std::cerr << "[SERVER::WARNING] Unknown method \"" + method_name + "\"." << std::endl;
    return nullptr;
}

void Manager::SendResponce(std::string& responce) {
    std::cout << "[SERVER] Sent responce:\n" << responce << std::endl;
    while (!responce.empty() && mSocketRef.is_open()) {
        boost::asio::write(mSocketRef, boost::asio::buffer(responce));
        responce.erase(0, responce.find_first_of('\0'));
    }
}

std::string Manager::GetErrorResult(std::string const& error_message) {
    return "{\"error\":\"" + error_message + "\"}";
}

}  // namespace request
