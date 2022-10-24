#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.2.0" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "542aee2bea509de7e185fc60b24a542c2cd44874-dirty" };
constexpr std::string_view GitCommitDate{ "Mon Oct 24 12:40:42 2022" };
constexpr std::string_view GitCommitMessage{ "add tree-like object hierarchy" };

} // namespace meov::definitions
