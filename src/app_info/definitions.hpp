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

constexpr std::string_view GitCommitHash{ "6c3e58dc9aa9f4c0fff475919dc789d361e7da81-dirty" };
constexpr std::string_view GitCommitDate{ "Mon Oct 24 10:12:43 2022" };
constexpr std::string_view GitCommitMessage{ "Initializer destructurization" };

} // namespace meov::definitions
