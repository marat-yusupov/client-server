#include <string>

#include <request/types/irequest.h>
#include <request/types/iresult.h>

namespace request::models {

class GetResult : public IResult {
public:
    GetResult();
    ~GetResult() override;

    rapidjson::Document ToJson() override;
};

class Get : public IRequest {
public:
    Get(std::string const& key);
    ~Get() override;

    virtual std::unique_ptr<IResult> Process() override;
};

}  // namespace request::models