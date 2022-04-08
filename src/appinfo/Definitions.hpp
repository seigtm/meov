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

constexpr std::string_view GitCommitHash{ "81ff4290d00b118847ee27276ea25af394a04711-dirty" };
constexpr std::string_view GitCommitDate{ "Thu Apr 7 20:01:42 2022" };
constexpr std::string_view GitCommitMessage{ "Manager::LoadProgram() return-flow fixes." };



} // namespace meov::definitions
