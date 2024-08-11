#pragma once

namespace request {

class IResult {
public:
    IResult() = default;
    virtual ~IResult() = default;

    virtual rapidjson::Document ToJson() = 0;
};

}  // namespace request
