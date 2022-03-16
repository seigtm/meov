#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.7" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "04cfd1a19dec087aa61957b09d585b16903c42d4-dirty" };
constexpr std::string_view GitCommitDate{ "Tue Mar 15 18:05:08 2022" };
constexpr std::string_view GitCommitMessage{ "First preudo-implementation of Settings singleton class." };



} // namespace meov::definitions
