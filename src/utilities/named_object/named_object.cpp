#include "common.hpp"

#include "named_object.hpp"


namespace meov::utilities {

NamedObject::NamedObject(const std::string &name) : mName{ name } {
    NamedObjectManager::Register(mName);
}

NamedObject::~NamedObject() {
    NamedObjectManager::UnRegister(mName);
}

const std::string &NamedObject::GetName() const {
    return mName;
}

NamedObjectManager *NamedObjectManager::Instance() {
    static NamedObjectManager manager;
    return &manager;
}

void NamedObjectManager::Register(const std::string &name) {
    if (name.empty()) {
        throw std::invalid_argument{ "Name is empty!" };
    }

    auto &registry{ NamedObjectManager::Instance()->mRegistry };
    auto found{ registry.find(name) };
    if (found == registry.end()) {
        registry[name] = true;
        return;
    } else if (!found->second) {
        found->second = true;
        return;
    }
    throw std::runtime_error{ "'" + name + "' already registered!" };
}

void NamedObjectManager::UnRegister(const std::string &name) {
    if (name.empty()) {
        return;
    }

    auto &registry{ NamedObjectManager::Instance()->mRegistry };
    if (auto found{ registry.find(name) }; found != registry.end()) {
        found->second = false;
    }
}

}  // namespace meov::utilities