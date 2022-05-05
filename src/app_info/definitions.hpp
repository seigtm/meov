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

constexpr std::string_view GitCommitHash{ "7abea73f16b75a6033957f87e3cea59a3d1044b6-dirty" };
constexpr std::string_view GitCommitDate{ "Tue May 3 15:24:22 2022" };
constexpr std::string_view GitCommitMessage{ "Refactoring in .gitattributes." };

} // namespace meov::definitions
