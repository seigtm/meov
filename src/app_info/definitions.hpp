#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.10" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "02887e233aeb71d76874ec47443b9e05cc54c81a-dirty" };
constexpr std::string_view GitCommitDate{ "Tue May 10 07:03:19 2022" };
constexpr std::string_view GitCommitMessage{ "Move ImGUi and STB to find modules" };

} // namespace meov::definitions
