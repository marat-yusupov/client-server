#include <fstream>
#include <iostream>
#include <sstream>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <data/config.h>

namespace data {

Config& Config::Instance() {
    static Config instance("/home/myuspv/Pets/client-server/server/config.txt");
    return instance;
}

Config::Config(std::string const& path) : mPath(path) {
    InitializeCachedValue();
}

Config::~Config() {}

std::string Config::Read(std::string const& key) {
    std::lock_guard locker(mConfigMutex);
    if (mCache.IsNull()) {
        std::cerr << "[SERVER::ERROR] File is empty" << std::endl;
        return std::string{};
    }

    if (!mCache.HasMember(key.c_str())) {
        std::cerr << "[SERVER::ERROR] Value with key \"" << key << "\" not found in config file" << std::endl;
        return std::string{};
    }

    return mCache[key.c_str()].GetString();
}

bool Config::Write(std::string const& key, std::string const& value) {
    std::lock_guard locker(mConfigMutex);
    std::ofstream file{mPath};
    if (!file.is_open()) {
        std::cerr << "[SERVER::ERROR] Failed opening file by path: \"" << mPath << "\"" << std::endl;
        std::cerr << "[SERVER::ERROR] Data not be writted" << std::endl;
        return false;
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

bool Config::InitializeCachedValue() {
    std::lock_guard locker(mConfigMutex);
    std::ifstream file{mPath};
    if (!file.is_open()) {
        std::cerr << "[SERVER::ERROR] Failed opening file by path: \"" << mPath << "\"" << std::endl;
        std::cerr << "[SERVER::ERROR] Cache not be updated" << std::endl;
        throw;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    mCache.Parse(buffer.str().c_str());

    return true;
}

}  // namespace data
