#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.8" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "070fd921da59bf0b307faffd75a5f616a2b0c7aa-dirty" };
constexpr std::string_view GitCommitDate{ "Wed Mar 16 17:35:37 2022" };
constexpr std::string_view GitCommitMessage{ "Assimp first shitty steps." };



} // namespace meov::definitions
