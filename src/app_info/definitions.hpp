#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.11" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "3e4fecfc6280a68a70f9544171fe4fbf48a18416-dirty" };
constexpr std::string_view GitCommitDate{ "Tue May 31 08:56:15 2022" };
constexpr std::string_view GitCommitMessage{ "IDK I just make one shit then another and now here's so much changes :cry:" };

} // namespace meov::definitions
