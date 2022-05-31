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

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "b85bab7b374b8ce579b0d635cf93218136299799-dirty" };
constexpr std::string_view GitCommitDate{ "Tue May 31 09:35:36 2022" };
constexpr std::string_view GitCommitMessage{ "add shaders hot reload (But as shit)" };

} // namespace meov::definitions
