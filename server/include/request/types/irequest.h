#pragma once

namespace request {

class IResult;

enum RequestName { Get, Set };

class IRequest {
public:
    IRequest() = default;
    virtual ~IRequest() = default;

    virtual RequestName Name() = 0;

    virtual std::unique_ptr<IResult> Process() = 0;
};

}  // namespace request
