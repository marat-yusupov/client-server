#include <fstream>
#include <iostream>
#include <sstream>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <data/config_handler.h>
#include <generic/log_utils.h>

namespace data {

ConfigHandler& ConfigHandler::Instance() {
    static ConfigHandler instance(CONFIG_PATH);
    return instance;
}

ConfigHandler::ConfigHandler(std::string const& path) : mPath(path) {
    InitCache();
}

ConfigHandler::~ConfigHandler() {}

std::string ConfigHandler::Read(std::string const& key) {
    std::lock_guard locker(mConfigMutex);
    if (mCache.IsNull()) {
        generic::LogErr(__func__, "File is empty");
        return std::string{};
    }

    if (!mCache.HasMember(key.c_str())) {
        generic::LogErr(__func__, "Value with key \"" + key + "\" not found in config file");
        return std::string{};
    }

    if (!mCache[key.c_str()].IsString()) {
        return std::string{};
    }

    return mCache[key.c_str()].GetString();
}

bool ConfigHandler::Write(std::string const& key, std::string const& value) {
    std::lock_guard locker(mConfigMutex);
    std::ofstream file{mPath};
    if (!file.is_open()) {
        generic::LogErr(__func__, "Failed opening file by path: \"" + mPath + "\"");
        generic::LogErr(__func__, "Data not be writted");
        return false;
    }

    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        mCache.Parse(buffer.str().c_str());
    }

    rapidjson::Value json_value(value.c_str(), mCache.GetAllocator());

    if (!mCache.HasMember(key.c_str())) {
        rapidjson::Value json_key(key.c_str(), mCache.GetAllocator());
        mCache.AddMember(json_key, json_value, mCache.GetAllocator());
    }

    mCache[key.c_str()] = json_value;

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    mCache.Accept(writer);

    file.clear();
    file << buffer.GetString();
    file.close();

    return true;
}

void ConfigHandler::InitCache() {
    std::lock_guard locker(mConfigMutex);
    std::ifstream file{mPath};
    if (!file.is_open()) {
        generic::LogErr(__func__, "Failed opening file by path: \"" + mPath + "\"");
        generic::LogErr(__func__, "Cache not be updated");
        throw;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    if (buffer.str().empty()) {
        mCache.SetObject();
        return;
    }

    mCache.Parse(buffer.str().c_str());
}

}  // namespace data
