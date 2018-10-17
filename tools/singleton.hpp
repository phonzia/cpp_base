#ifndef _SINGLETON_HPP_14_
#define _SINGLETON_HPP_14_
#include <memory>
#include <mutex>
#include <cassert>
#include <type_traits>

namespace cppbase{
template <typename T>
class Singleton {
public:
    template <typename... Args>
    static std::shared_ptr<T> sharedInstance(Args &&... args) {
        std::call_once(s_onceFlag, [&] {
            Singleton<T>::s_sharedInstance = std::make_shared<T>(std::forward<Args>(args)...);
        });
        return Singleton<T>::s_sharedInstance;
    }

    template <typename R = T>
    static std::shared_ptr < typename std::enable_if_t < !std::is_default_constructible<R>::value, R >>
    sharedInstance() {
        assert(s_sharedInstance != nullptr);
        return Singleton<T>::s_sharedInstance;
    }

    template <typename R = T>
    static std::shared_ptr<typename std::enable_if_t<std::is_default_constructible<R>::value, R>>
    sharedInstance() {
        std::call_once(s_onceFlag, [&] {
            Singleton<T>::s_sharedInstance = std::make_shared<T>();
        });
        return Singleton<T>::s_sharedInstance;
    }

private:
    static std::shared_ptr<T> s_sharedInstance;
    static std::once_flag s_onceFlag;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::s_sharedInstance = nullptr;

template <typename T>
std::once_flag Singleton<T>::s_onceFlag;
}

#endif
