#include <common>
#include "utils/log_storage/log_storage.hpp"
#include <utils/log_utils.hpp>

namespace meov::utils::Log {

//====================== Storage::Subscriber =====================//

void Storage::Subscriber::OnSubscribe(ContainerRef storage) {
    mStorage = storage;
}

void Storage::Subscriber::OnUnsubscribe() {
    mStorage.reset();
}

//========================== Storage =============================//

Storage::Storage()
    : mStorage{ new Container } {}

void Storage::write(const plog::Record& record) {
    mStorage->emplace_back(DefaultFormatter::format(record));
    // FIXME: Why do we even need OnStorageUpdate()?
    // for(auto&& weakptr : mSubscribers) {
    //     if(auto sub{ weakptr.lock() }; sub != nullptr) {
    //         sub->OnStorageUpdate();
    //     }
    // }
}

void Storage::Subscribe(const Subscriber::Ref& s) {
    if(s == nullptr) {
        return;
    }
    mSubscribers.emplace_back(s);
    s->OnSubscribe(mStorage);
}

void Storage::Unsubscribe(const Subscriber::Ref& s) {
    mSubscribers.remove_if(
        [s](auto&& x) {
            auto ptr = x.lock();
            s->OnUnsubscribe();
            return ptr == s;
        });
}

}  // namespace meov::utils::Log
