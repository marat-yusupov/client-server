#include <chrono>
#include <format>
#include <thread>

#include <generic/log_utils.h>

#include <request/statistic.h>
#include <request/types/irequest.h>

namespace request {

Statistic& Statistic::Instance() {
    static Statistic instance;
    return instance;
}

Statistic::Statistic() {
    auto start_time = std::chrono::high_resolution_clock::now();
    mStatisticPrinter = std::thread([&]() {
        for (;;) {
            std::this_thread::sleep_for(std::chrono::seconds(2));

            Print();
            mReadLastFiveSeconds = 0;
            mWriteLastFiveSeconds = 0;
        }
    });
}

Statistic::~Statistic() {
    if (mStatisticPrinter.joinable()) {
        mStatisticPrinter.join();
    }
}

void Statistic::Apply(RequestName request_name) {
    switch (request_name) {
        case RequestName::Get:
            mReadLastFiveSeconds++;
            mReadAllTime++;
            break;
        case RequestName::Set:
            mWriteLastFiveSeconds++;
            mWriteAllTime++;
            break;
        default:
            break;
    }
}

void Statistic::Print() {
    // clang-format off
    std::string printable_data = std::format(R"(

[READ REQUEST INVOKE STATISTICS]:
    Last 5 seconds: {}
    All: {}

[WRITE REQUEST INVOKE STATISTICS]:
    Last 5 seconds: {}
    All: {}
    
)", 
    
    mReadLastFiveSeconds.load(), mReadAllTime.load(), 
    mWriteLastFiveSeconds.load(), mWriteAllTime.load());
    // clang-format on

    generic::Log(printable_data);
}

}  // namespace request
