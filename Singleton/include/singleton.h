#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>

template<typename T>
class Singleton
{
private:
    static std::shared_ptr<Singleton> uniqueInstance;
    T data;
    std::mutex m;
    static std::once_flag singleton_init_flag;
    Singleton() { }
    static void init_resource()
    {
        std::shared_ptr<Singleton> temp(new Singleton());
        uniqueInstance = temp;
    }
public:
    ~Singleton() { }
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&);
    static std::shared_ptr<Singleton> getInstance() { std::call_once(singleton_init_flag, &Singleton::init_resource); return uniqueInstance; };
    void set(const T& data_) { std::lock_guard<std::mutex> lk(m); data = data_; }
    T& get() { std::lock_guard<std::mutex> lk(m); return data; }
};

template<typename T> Singleton<T>& Singleton<T>::operator=(Singleton&& other)
{
    std::scoped_lock guard(m, other.m);
    uniqueInstance = other.uniqueInstance;
    other.uniqueInstance = nullptr;
    data = std::move(other.data);
    return *this;
}

#endif // SINGLETON_H
