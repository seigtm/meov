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

constexpr std::string_view GitCommitHash{ "7e33270e53bde3c1b08f86220797503027c5412a-dirty" };
constexpr std::string_view GitCommitDate{ "Thu May 26 16:10:49 2022" };
constexpr std::string_view GitCommitMessage{ "Merge branch 'master' into Baranov_Skybox" };

} // namespace meov::definitions
