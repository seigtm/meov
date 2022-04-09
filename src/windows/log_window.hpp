#pragma once

#include "common.hpp"
#include "utilities.hpp"
#include "log_utils.hpp"
#include "windows/base_window.hpp"

namespace meov::Window {

class Log final : public Base, public utils::Log::Storage::Subscriber {
public:
    using Reference = std::shared_ptr<Log>;  // FIXME: ambiguous '::Ref' from Subscriber.
    explicit Log(std::string_view const title, ImVec2 const& size = { 650, 200 });

protected:
    void DrawImpl() override final;
    static ImVec4 GetColorFor(const std::string_view& line);
};

}  // namespace meov::Window