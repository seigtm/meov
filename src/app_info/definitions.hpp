#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.9" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "83137a0f8abf8449bc9b8de16d7fc7418119a04c-dirty" };
constexpr std::string_view GitCommitDate{ "Sat Apr 9 12:02:35 2022" };
constexpr std::string_view GitCommitMessage{ "Fixed links in shaders.md mermaid diagram." };

} // namespace meov::definitions
