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

constexpr std::string_view GitCommitHash{ "0da2f0196c7644227b5f7327d7e2747d99f1bf36-dirty" };
constexpr std::string_view GitCommitDate{ "Mon Apr 11 13:54:41 2022" };
constexpr std::string_view GitCommitMessage{ "GLM as submodule instead of conan package." };

} // namespace meov::definitions
