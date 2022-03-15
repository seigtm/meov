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

constexpr std::string_view GitCommitHash{ "5295ef491a69678ba6e1b3620163e463be9831af" };
constexpr std::string_view GitCommitDate{ "Tue Mar 15 10:11:41 2022" };
constexpr std::string_view GitCommitMessage{ "Merge pull request #12 from seigtm/Golovinsky_Refactoring" };



} // namespace meov::definitions
