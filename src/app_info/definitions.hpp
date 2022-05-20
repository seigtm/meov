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

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "0c53e4d3ed7ff127c03c5f49d21f3e06895846c8-dirty" };
constexpr std::string_view GitCommitDate{ "Thu May 19 13:00:06 2022" };
constexpr std::string_view GitCommitMessage{ "Tried to make visible lighting" };

} // namespace meov::definitions
