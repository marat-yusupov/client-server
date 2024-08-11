#include <memory>
#include <string>

namespace request {

class IRequest;

class Manager {
public:
    Manager();
    ~Manager();

    std::string Process(std::string const& request_json_as_string);

private:
    std::unique_ptr<IRequest> Prepare(std::string const& request_json_as_string);

    std::string GetErrorResultJSON(std::string const& error_message);
};

}  // namespace request
