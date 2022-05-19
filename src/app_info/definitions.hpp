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

constexpr std::string_view GitCommitHash{ "cbee06ab7d9437e2e7d61c10c1a1b504a01d78d5-dirty" };
constexpr std::string_view GitCommitDate{ "Thu May 19 09:05:20 2022" };
constexpr std::string_view GitCommitMessage{ "Add transform and properties" };

} // namespace meov::definitions
