#pragma once

#include <mutex>
#include <string>

#include <rapidjson/document.h>

namespace data {

class Config {
public:
    static Config& Instance();
    ~Config();

    std::string Read(std::string const& key);
    bool Write(std::string const& key, std::string const& value);

private:
    Config(std::string const& path);

    void ValidateCache();

    std::string mPath;
    std::mutex mConfigMutex;
    rapidjson::Document mCache;
};

}  // namespace data
