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

constexpr std::string_view GitCommitHash{ "f9301dfdc81c77996671c33a072f1dcac2917937-dirty" };
constexpr std::string_view GitCommitDate{ "Mon May 30 13:05:21 2022" };
constexpr std::string_view GitCommitMessage{ "Check that all skybox images have the same width, height and number of channels" };

} // namespace meov::definitions
