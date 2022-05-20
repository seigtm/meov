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

constexpr std::string_view LogLevel{ "Release" };

constexpr std::string_view GitCommitHash{ "4386b57941ed22cdc5b4e2d624ade8c4cfe3a556-dirty" };
constexpr std::string_view GitCommitDate{ "Fri May 20 09:29:32 2022" };
constexpr std::string_view GitCommitMessage{ "Clean main.cpp" };

} // namespace meov::definitions
