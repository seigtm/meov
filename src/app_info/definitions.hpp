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

constexpr std::string_view GitCommitHash{ "f8e0d39e83a79f0b42b4b9b00f8c00033bf2f727-dirty" };
constexpr std::string_view GitCommitDate{ "Sat Apr 9 09:29:00 2022" };
constexpr std::string_view GitCommitMessage{ "FLY Mazafaka" };

} // namespace meov::definitions
