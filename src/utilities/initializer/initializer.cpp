#include "common.hpp"

#include "initializer.hpp"

namespace meov::utilities {

Initializer::Initializer(InitializerListener *parent, std::string &&name, Task &&onInit, Task &&onDestroy)
    : mParent{ parent }
    , mName{ std::move(name) }
    , mDestroyTask{ std::move(onDestroy) } {
    LOGI << "Initialize " << mName;
    LogStatus(onInit(), " was initialized successfully", "Cannot initialize ");
}

Initializer::~Initializer() {
    LOGI << "Destroying " << mName;
    LogStatus(mDestroyTask(), " was destroyed successfully", "Cannot destroy");
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
