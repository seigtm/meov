#pragma once

#include <memory>

namespace meov::Utils {

template<class Base>
class AsReference {
public:
    using Ref = std::shared_ptr<Base>;
    using WeakRef = std::weak_ptr<Base>;
    using Ptr = std::unique_ptr<Base>;
};

template<class Base>
class NonCopyable {
public:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
    Base &operator=(const Base &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

template<class Base>
class Singleton : public NonCopyable<Base> {
public:
    static Base *Instance() {
        static Base inst;
        return &inst;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};

}  // namespace meov::Utils
