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

constexpr std::string_view GitCommitHash{ "2839200b4c78e1f0821554f940f78811b118071a-dirty" };
constexpr std::string_view GitCommitDate{ "Tue Oct 25 14:32:22 2022" };
constexpr std::string_view GitCommitMessage{ "Merge pull request #17 from seigtm/Golovinsky_Refactoring_And_improvements" };

} // namespace meov::definitions
