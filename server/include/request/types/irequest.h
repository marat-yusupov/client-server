#pragma once

namespace request {

class IResult;

class IRequest {
public:
    IRequest() = default;
    virtual ~IRequest() = default;

    virtual std::unique_ptr<IResult> Process() = 0;
};

}  // namespace request
