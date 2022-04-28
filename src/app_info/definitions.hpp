#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.9" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "86503c3267a3926b1faf49001168b2ab6791978c-dirty" };
constexpr std::string_view GitCommitDate{ "Sun Apr 24 12:56:09 2022" };
constexpr std::string_view GitCommitMessage{ "Updated app info, app after reverting commit works kinda fine.." };

} // namespace meov::definitions
