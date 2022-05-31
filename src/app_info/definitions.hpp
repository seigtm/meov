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

constexpr std::string_view GitCommitHash{ "58f3cc0612aeb2a464dc1272770640fb708221de-dirty" };
constexpr std::string_view GitCommitDate{ "Mon May 30 23:06:09 2022" };
constexpr std::string_view GitCommitMessage{ "Merge pull request #15 from seigtm/Baranov_Skybox" };

} // namespace meov::definitions
