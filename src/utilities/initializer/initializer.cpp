#include "common.hpp"

#include "initializer.hpp"

namespace meov::utilities {

Initializer::Initializer(Listener *parent, std::string &&name, Task &&onInit, Task &&onDestroy)
    : mParent{ parent }
    , mName{ std::move(name) }
    , mDestroyTask{ std::move(onDestroy) } {
    LOGI << "Initialize " << mName;
    LogStatus(onInit(), " was initialized successfly", "Cannot initialize ");
}

Initializer::~Initializer() {
    LOGI << "Destroying " << mName;
    LogStatus(mDestroyTask(), " was destroyed successfly", "Cannot destroy");
}

void Initializer::LogStatus(bool success, const std::string_view successMessage, const std::string_view failedMessage) const {
    if(success) {
        LOGI << mName << successMessage;
        return;
    }
    LOGE << failedMessage << mName;
    if(mParent) {
        mParent->OnFail(mName);
    }
}

}  // namespace meov::utilities
