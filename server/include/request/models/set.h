#include <string>

#include <request/types/irequest.h>
#include <request/types/iresult.h>

namespace request::models {

class SetResult : public IResult {
public:
    SetResult();
    ~SetResult() override;

    rapidjson::Document ToJson() override;
};

class Set : public IRequest {
public:
    Set(std::string const& key, std::string const& new_value);
    ~Set() override;

    virtual std::unique_ptr<IResult> Process() override;
};

}  // namespace request::models