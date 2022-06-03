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

constexpr std::string_view LogLevel{ "Release" };

constexpr std::string_view GitCommitHash{ "dff7ade459716665b3f4a46db942e2ae7286584d-dirty" };
constexpr std::string_view GitCommitDate{ "Thu Jun 2 20:21:16 2022" };
constexpr std::string_view GitCommitMessage{ "Massive renaming, again (forgot Transformable.cpp)." };

} // namespace meov::definitions
