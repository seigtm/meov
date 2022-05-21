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

constexpr std::string_view GitCommitHash{ "f11c8279e94750a5f61890391b7ecc72a51d0376-dirty" };
constexpr std::string_view GitCommitDate{ "Sat May 21 10:57:20 2022" };
constexpr std::string_view GitCommitMessage{ "Removed flip-UV Assimp flag." };

} // namespace meov::definitions
