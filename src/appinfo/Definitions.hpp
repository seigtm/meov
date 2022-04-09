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

constexpr std::string_view GitCommitHash{ "4ecd5cb6f4df865394fb909f8df8dca4d1a701e7-dirty" };
constexpr std::string_view GitCommitDate{ "Fri Apr 8 15:38:49 2022" };
constexpr std::string_view GitCommitMessage{ "assets/models/backpack/backpack.obj: convert to Git LFS" };



} // namespace meov::definitions
