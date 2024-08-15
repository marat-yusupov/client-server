#pragma once

#include <string>

#include <rapidjson/document.h>

namespace data {

class Config {
public:
    Config(std::string const& path);
    ~Config();

    std::string Read(std::string const& key);
    bool Write(std::string const& key, std::string const& value);

private:
    bool InitializeCachedValue();

    std::string mPath;
    rapidjson::Document mContent;
};

}  // namespace data
