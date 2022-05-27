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

constexpr std::string_view GitCommitHash{ "0e779d1f26ab6ee4916163365b776778435e4036-dirty" };
constexpr std::string_view GitCommitDate{ "Fri May 27 07:56:04 2022" };
constexpr std::string_view GitCommitMessage{ "skybox_component aroundwork" };

} // namespace meov::definitions
