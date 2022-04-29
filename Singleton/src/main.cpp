#include <memory>
#include <iostream>
#include <latch>
#include <thread>
#include <atomic>
#include <vector>
#include "singleton.h"

template<typename T> std::shared_ptr<Singleton<T>> Singleton<T>::uniqueInstance{nullptr};
template<typename T> std::once_flag Singleton<T>::singleton_init_flag;

std::atomic<bool> go(false);
std::mutex iom;

using id = std::thread::id;

void task(std::latch& done)
{
    while (!go)
    {
        std::this_thread::yield();
    }
    std::shared_ptr<Singleton<id>> singleton = Singleton<id>::getInstance();
    id this_thread_id = std::this_thread::get_id();
    singleton->set(this_thread_id);
    done.count_down();
    while (go)
    {
        std::this_thread::yield();
    }
    {
        std::lock_guard<std::mutex> lk(iom);
        std::cout << singleton->get() << std::endl;
    }
}

int main()
{
    size_t threads_number = 5;
    std::latch done(threads_number);
    std::vector<std::thread> threads(threads_number);
    for (auto& i : threads)
    {
        i = std::thread(task,std::ref(done));
    }
    go = true;
    done.wait();
    std::shared_ptr<Singleton<id>> singleton = Singleton<id>::getInstance();
    std::cout << singleton->get() << "\n" << std::endl;
    go = false;
    for (auto& i : threads)
    {
        if (i.joinable())
        {
            i.join();
        }
    }
    return 0;
}
