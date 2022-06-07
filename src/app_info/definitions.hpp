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

constexpr std::string_view GitCommitHash{ "e35e6ea36b02bbe7820423d87f0274a5cb4084ef-dirty" };
constexpr std::string_view GitCommitDate{ "Tue Jun 7 19:43:19 2022" };
constexpr std::string_view GitCommitMessage{ "Updated models and changed some default values." };

} // namespace meov::definitions
