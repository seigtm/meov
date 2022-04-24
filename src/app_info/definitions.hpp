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

constexpr std::string_view GitCommitHash{ "d49d674da8a45f16ffcc517b8d0bdd558af21067" };
constexpr std::string_view GitCommitDate{ "Mon Apr 11 16:56:15 2022" };
constexpr std::string_view GitCommitMessage{ "Every dependency is now git submodule, not conan package." };

} // namespace meov::definitions
