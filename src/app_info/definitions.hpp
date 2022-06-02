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

constexpr std::string_view GitCommitHash{ "a275db5512872281b1dfa84079be8fd9114650bd-dirty" };
constexpr std::string_view GitCommitDate{ "Thu Jun 2 20:01:54 2022" };
constexpr std::string_view GitCommitMessage{ "Fixed version and renamed SHIT_SHIT_SHIT to mWindows." };

} // namespace meov::definitions
