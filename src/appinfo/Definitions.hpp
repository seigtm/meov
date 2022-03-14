#pragma once

#include <string_view>

namespace meov::definitions {

constexpr bool UsingOpenGL{ true };
constexpr bool UsingVulcan{ false };

constexpr std::string_view Version{ "v0.1.7" };
constexpr unsigned ShaderVersionMajor{ 4 };
constexpr unsigned ShaderVersionMinor{ 5 };
constexpr unsigned ShaderVersionPatch{ 0 };
constexpr std::string_view ShaderVersion{ "#version 450 core" };
constexpr std::string_view Program_name{ "MEOV | Minimalistic Easy Object Viewer" };

constexpr std::string_view LogLevel{ "Debug" };

constexpr std::string_view GitCommitHash{ "a69df98e10608cdba5e0c1e450aaee87264d733d-dirty" };
constexpr std::string_view GitCommitDate{ "Sun Mar 13 11:35:07 2022" };
constexpr std::string_view GitCommitMessage{ "Refactor FrameBuffer" };



} // namespace meov::definitions
