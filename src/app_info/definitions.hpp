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

constexpr std::string_view GitCommitHash{ "8d64764a99592970b5cc2aae79e11c339fc1d545-dirty" };
constexpr std::string_view GitCommitDate{ "Sat Apr 9 11:50:18 2022" };
constexpr std::string_view GitCommitMessage{ "Made the backpack model fit on the screen." };

} // namespace meov::definitions
