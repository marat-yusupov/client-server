#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

namespace generic {

class ThreadPool {
    constexpr static int MAX_THREAD_COUNT_DEFAULT = 10;

public:
    explicit ThreadPool(int max_thread_count = MAX_THREAD_COUNT_DEFAULT);
    ~ThreadPool();

    template <typename TaskType, typename... Args>
    void Enqueue(TaskType&& task, Args&&... args) {
        {
            std::unique_lock lock(mQueueMutex);
            if (mStop)
                throw std::runtime_error("Enqueue on stopped ThreadPool");
            mTaskList.emplace([=]() { task(std::forward<Args>(args)...); });
        }
        mCondition.notify_one();
    }

private:
    std::vector<std::thread> mWorkerList;
    std::queue<std::function<void()>> mTaskList;
    std::mutex mQueueMutex;
    std::condition_variable mCondition;
    bool mStop;
};

}  // namespace generic
