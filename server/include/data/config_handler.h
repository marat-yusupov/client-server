#pragma once

#include <mutex>
#include <string>

#include <rapidjson/document.h>

namespace data {

class ConfigHandler {
public:
    static ConfigHandler& Instance();
    ~ConfigHandler();

    std::string Read(std::string const& key);
    bool Write(std::string const& key, std::string const& value);

private:
    ConfigHandler(std::string const& path);

    void InitCache();

    std::string mPath;
    std::mutex mConfigMutex;
    rapidjson::Document mCache;
};

}  // namespace data
