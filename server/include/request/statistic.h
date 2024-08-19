#include <atomic>
#include <memory>

#include <request/types/irequest.h>

namespace request {

class Statistic {
public:
    static Statistic& Instance();
    ~Statistic();

    void Apply(RequestName request_name);

private:
    Statistic();

    void Print();

    std::thread mStatisticPrinter;

    std::atomic<int> mReadAllTime = 0;
    std::atomic<int> mWriteAllTime = 0;

    std::atomic<int> mReadLastFiveSeconds = 0;
    std::atomic<int> mWriteLastFiveSeconds = 0;
};

}  // namespace request
