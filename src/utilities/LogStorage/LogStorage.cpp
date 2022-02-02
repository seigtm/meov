#include "Common.hpp"
#include "LogStorage.hpp"
#include "LogUtils.hpp"

namespace MEOV::Utils::Log {

//====================== Storage::Subscriber =====================//

void Storage::Subscriber::OnSubscribe(ContainerRef storage) {
    mStorage = storage;
}

void Storage::Subscriber::OnStorageUpdate() {}

//========================== Storage =============================//

void Storage::write(const plog::Record& record) {
    mStorage->emplace_back(DefaultFormatter::format(record));
    for(auto&& weakptr : mSubscribers) {
        if(auto sub{ weakptr.lock() }; sub != nullptr) {
            sub->OnStorageUpdate();
        }
    }
}

void Storage::Subscribe(const Subscriber::Ref& s) {
    if(s == nullptr) {
        return;
    }
    mSubscribers.emplace_back(s);
    s->OnSubscribe(mStorage);
}

void Storage::Unsubscribe(const Subscriber::Ref& s) {
    // mSubscribers.remove(s);
}


}  // namespace MEOV::Utils::Log
