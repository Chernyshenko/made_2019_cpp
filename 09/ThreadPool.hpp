
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

    bool stop_pool;
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};


ThreadPool::ThreadPool(size_t poolSize) : stop_pool(false){

    for(size_t i = 0; i < poolSize; i++){
        pool.emplace_back([this](){
            while(true)
            {
                Task task;
                {
                    std::unique_lock<std::mutex> lock(func_mutex);
                    newFunc.wait(lock, 
                        [this]()
                        { 
                            return !tasks.empty() || stop_pool;
                        });

                    if (tasks.empty() || stop_pool)
                        return;

                    task = tasks.front();
                    tasks.pop();
                }
                task();
            }
        });
    }
}
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(func_mutex);
        stop_pool = true;
    }
    newFunc.notify_all();
    for (auto& t : pool)
    {
        t.join();
    }
}

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

