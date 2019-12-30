#include "ThreadPool.hpp"


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
                            return !tasks.empty() || stop_pool.load();
                        });

                    if (tasks.empty() || stop_pool.load())
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
    stop_pool.store(true);
    newFunc.notify_all();
    for (auto& t : pool)
    {
        t.join();
    }
}

