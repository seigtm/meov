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

constexpr std::string_view GitCommitHash{ "4b6cd9a1a2e4a6e92851244be6fa3d15aa7e7ff4" };
constexpr std::string_view GitCommitDate{ "Mon Mar 14 14:25:04 2022" };
constexpr std::string_view GitCommitMessage{ "Lil core shaders refactoring" };



} // namespace meov::definitions
