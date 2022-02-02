#pragma once

#include "Utilities.hpp"

namespace MEOV::Utils::Log {

class Storage final : public AsReference<Storage>, public plog::IAppender {
public:
    using Container = std::vector<plog::util::nstring>;
    using ContainerRef = std::shared_ptr<Container>;

    class Subscriber : public AsReference<Subscriber> {
    public:
        virtual void OnSubscribe(ContainerRef storage);
        virtual void OnStorageUpdate();

    protected:
        std::weak_ptr<Container> mStorage;
    };

    Storage()
        : mStorage{ new Container } {}

    // Overriden write method of IAppender.
    void write(const plog::Record& record) override final;

    void Subscribe(const Subscriber::Ref& s);
    void Unsubscribe(const Subscriber::Ref& s);

private:
    ContainerRef mStorage;
    std::list<Subscriber::WeakRef> mSubscribers;
};


}  // namespace MEOV::Utils::Log
