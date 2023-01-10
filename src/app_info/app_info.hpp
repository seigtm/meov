#pragma once

#include <string_view>

namespace meov {

struct AppInfo {
    [[nodiscard]] static constexpr std::string_view Version() noexcept { return "v0.2.0"; }

    [[nodiscard]] static constexpr std::string_view GLSLVersion() noexcept {
        return "#version 450 core";
    }

    [[nodiscard]] static constexpr size_t GLSLVersionMajor() noexcept { return 4; }
    [[nodiscard]] static constexpr size_t GLSLVersionMinor() noexcept { return 5; }
    [[nodiscard]] static constexpr size_t GLSLVersionPatch() noexcept { return 0; }

    [[nodiscard]] static constexpr std::string_view Name() noexcept { return
        "MEOV | Minimalistic Easy Object Viewer";
    }

    [[nodiscard]] static constexpr std::string_view LogLevel() noexcept { return "Debug"; }

    [[nodiscard]] static constexpr bool IsDebugMode() noexcept {
        #if defined(_DEBUG)
            return true;
        #else
            return false;
        #endif
    }
    [[nodiscard]] static constexpr bool IsOpenGL() noexcept { return true; }
    [[nodiscard]] static constexpr bool IsVulkan() noexcept { return false; }

};

}  // namespace meov
