#pragma once

#include <memory>

namespace MEOV::Utils {

template<class Base>
class AsReference {
public:
    using Ref = std::shared_ptr<Base>;
    using Ptr = std::unique_ptr<Base>;
};

template<class Base>
class NonCopyable {
public:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
    Base &operator =(const Base &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

template<class Base>
class NonMovable {
public:
    NonCopyable(NonCopyable &&) = delete;
    NonCopyable &operator=(NonCopyable &&) = delete;
    Base &operator =(Base &&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

template<class Base>
class Singleton {
public:
    static Base *Instance() {
        static Base inst;
        return &inst;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};

} // namespace MEOV::Utils
