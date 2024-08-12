#include <string>

#include <request/types/irequest.h>
#include <request/types/iresult.h>

namespace request::models {

class GetResult : public IResult {
public:
    GetResult(std::string const& value);
    ~GetResult() override;

    rapidjson::Document ToJson() override;

private:
    std::string mValue;
};

class Get : public IRequest {
public:
    Get(std::string const& key);
    ~Get() override;

    virtual std::unique_ptr<IResult> Process() override;

private:
    std::string mKey;
};

}  // namespace request::models