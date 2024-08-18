#include <generic/thread_pool.h>

namespace generic {

ThreadPool::ThreadPool(int max_thread_count) : mStop(false) {
    for (int i = 0; i < max_thread_count; i++) {
        mWorkerList.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock lock(mQueueMutex);
                    mCondition.wait(lock, [this] { return this->mStop || !mTaskList.empty(); });
                    if (mStop && mTaskList.empty())
                        return;
                    task = std::move(mTaskList.front());
                    mTaskList.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock(mQueueMutex);
        mStop = true;
    }
    mCondition.notify_all();
    for (auto& worker : mWorkerList)
        worker.join();
}

}  // namespace generic
