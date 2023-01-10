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

constexpr std::string_view GitCommitHash{ "ddb8f5e2fe20c95d1d3cbfa6c992209dc0736979-dirty" };
constexpr std::string_view GitCommitDate{ "Wed Oct 26 09:28:14 2022" };
constexpr std::string_view GitCommitMessage{ "Add todo shit" };

} // namespace meov::definitions
