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

constexpr std::string_view LogLevel{ "Release" };

constexpr std::string_view GitCommitHash{ "6c520de24d2e112620f849cb1bb416882a9addb3-dirty" };
constexpr std::string_view GitCommitDate{ "Sat Jun 4 11:48:24 2022" };
constexpr std::string_view GitCommitMessage{ "Removed one model and added other one." };

} // namespace meov::definitions
