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

constexpr std::string_view GitCommitHash{ "afe4fae02c40e543a2217efcb26bf6b36bade0e2-dirty" };
constexpr std::string_view GitCommitDate{ "Thu May 12 10:17:25 2022" };
constexpr std::string_view GitCommitMessage{ "Small refactoring of widgets." };

} // namespace meov::definitions
