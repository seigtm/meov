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

constexpr std::string_view GitCommitHash{ "8061fef27a845253e49b43405d63c4ad1c46a096" };
constexpr std::string_view GitCommitDate{ "Mon Oct 24 17:15:35 2022" };
constexpr std::string_view GitCommitMessage{ "Another stuff for adding object to the scene" };

} // namespace meov::definitions
