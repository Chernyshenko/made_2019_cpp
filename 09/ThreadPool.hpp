#pragma once
#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>
#include <atomic>

class ThreadPool
{
private:
    using Task = std::function<void ()>; //std::packaged_task<void ()>;
    std::vector<std::thread> pool;
    std::mutex func_mutex;
    std::condition_variable newFunc;
    std::queue<Task> tasks;
    std::atomic<bool> stop_pool;
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>{

    //std::packaged_task<decltype(func(args...))(Args...)> task(std::bind(func, args...));
    auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>> (std::bind(func, args...));

    auto future_res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(func_mutex);
        //tasks.push(Task(std::move(task)));
        tasks.push([=](){ (*task)(); });
    }

    newFunc.notify_one();

    return future_res;
}
