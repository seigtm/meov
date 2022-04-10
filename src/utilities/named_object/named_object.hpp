#pragma once

#include <string>
#include <unordered_map>

namespace meov::utilities {

class NamedObject {
public:
    explicit NamedObject(const std::string &name);
    virtual ~NamedObject();

    const std::string &GetName() const;

private:
    std::string mName;
};

class NamedObjectManager {
public:
    static NamedObjectManager *Instance();

    static void Register(const std::string &name);
    static void UnRegister(const std::string &name);

private:
    NamedObjectManager() = default;

    std::unordered_map<std::string, bool> mRegistry;
};

}  // namespace meov::utilities