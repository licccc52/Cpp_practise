#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unistd.h>

class ThreadPool {
public:
    ThreadPool(size_t threadnum);
    ~ThreadPool();

    void submit(void (*task)());

    void stop();

private:
    std::vector<std::thread> threads_;
    std::queue<void (*)()> taskqueue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};

ThreadPool::ThreadPool(size_t threadnum) : stop_(false) {
    for (size_t ii = 0; ii < threadnum; ii++) {
        threads_.emplace_back([this]() {
            std::cout << "Thread " << std::this_thread::get_id() << " created." << std::endl;
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    condition_.wait(lock, [this] { return stop_ || !taskqueue_.empty(); });
                    if (stop_ && taskqueue_.empty()) return;
                    task = taskqueue_.front();
                    taskqueue_.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop();
}

void ThreadPool::submit(void (*task)()) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        taskqueue_.push(task);
    }
    condition_.notify_one();
}

void ThreadPool::stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    condition_.notify_all();
    for (auto& thread : threads_) {
        thread.join();
    }
}

// Test function
void printHello() {
    std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    ThreadPool pool(4);

    // Submit tasks to the pool
    for (int i = 0; i < 10; ++i) {
        pool.submit(printHello);
        usleep(100000); // Sleep for 0.1 second
    }

    // Stop the pool
    pool.stop();

    return 0;
}
