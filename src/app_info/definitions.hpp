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

constexpr std::string_view LogLevel{ "Release" };

constexpr std::string_view GitCommitHash{ "c1a6eb1f10f449e4c7ce4ca6138e53e4d534e144-dirty" };
constexpr std::string_view GitCommitDate{ "Thu Apr 28 14:53:15 2022" };
constexpr std::string_view GitCommitMessage{ "Toolbar, open model file dialog, toggle visibilities and other cringy implementation from me :)." };

} // namespace meov::definitions
