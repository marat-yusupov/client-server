#include <string>

#include <request/types/irequest.h>
#include <request/types/iresult.h>

namespace request::models {

class SetResult : public IResult {
public:
    SetResult(bool is_success = true);
    ~SetResult() override;

    rapidjson::Document ToJson() override;

private:
    bool mIsSuccess;
};

class Set : public IRequest {
public:
    Set(std::string const& key, std::string const& new_value);
    ~Set() override;

    virtual std::unique_ptr<IResult> Process() override;

private:
    std::string mKey;
    std::string mNewValue;
};

}  // namespace request::models