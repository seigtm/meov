#pragma once

#include "Base.hpp"
#include <memory>
#include <list>

namespace meov::Window {

class Value {
public:
    using Shared = std::shared_ptr<Value>;

    explicit Value(const std::string &name, bool readOnly = true);
    explicit Value(std::string &&name, bool readOnly = true);

    virtual void Draw() = 0;

    const std::string &GetTitle() const;

protected:
    std::string mTitle{};
    bool mReadOnly{ true };
};

class Parameters final : public Base {
public:
    explicit Parameters(const std::string_view &title, const ImVec2 &size = {});

    Parameters &Add(const Value::Shared &value);

private:
    std::list<Value::Shared> mValues;

    void DrawImpl() override;
};

}  // namespace meov::Window