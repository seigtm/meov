#pragma once

#include <functional>
#include <string>
#include <set>

namespace meov::utils {

class InitializerListener;

class Initializer final {
public:
    using Shared = std::shared_ptr<Initializer>;
    using Task = std::function<bool()>;

    Initializer(InitializerListener *parent, std::string &&name, Task &&onInit, Task &&onDestroy) noexcept;
    ~Initializer();

private:
    InitializerListener *mParent;
    std::string mName;
    Task mDestroyTask;

    void LogStatus(bool success,
                   const std::string_view successMessage,
                   const std::string_view failedMessage) const;
};

}  // namespace meov::utils