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

constexpr std::string_view GitCommitHash{ "25a10f7fc1617272aceb36e71bc9fe4ce480a107-dirty" };
constexpr std::string_view GitCommitDate{ "Sun May 22 13:49:11 2022" };
constexpr std::string_view GitCommitMessage{ "SHitted scene and its treee" };

} // namespace meov::definitions
