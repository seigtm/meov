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

constexpr std::string_view GitCommitHash{ "6dd2a4e150e6e24b4380b55bac64a50a55e30858-dirty" };
constexpr std::string_view GitCommitDate{ "Mon May 30 20:36:07 2022" };
constexpr std::string_view GitCommitMessage{ "Merge branch Baranov_Skybox into Golovinsky_Lighting" };

} // namespace meov::definitions
