#pragma once

#include "Common.hpp"
#include "Utilities.hpp"
#include "LogUtils.hpp"
#include "windows/Base.hpp"

namespace meov::Window {

class Log final : public Base, public Utils::Log::Storage::Subscriber {
public:
    using Reference = std::shared_ptr<Log>;  // FIXME: ambiguous '::Ref' from Subscriber.
    Log(std::string_view const title);

protected:
    void DrawImpl() override final;
};

}  // namespace meov::Window
