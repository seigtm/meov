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

constexpr std::string_view LogLevel{ "Release" };

constexpr std::string_view GitCommitHash{ "3908a6f2410642529342131722b9049e89688bda-dirty" };
constexpr std::string_view GitCommitDate{ "Mon Apr 11 15:51:44 2022" };
constexpr std::string_view GitCommitMessage{ "SDL and GLBinding as submodules instead of conan packages." };

} // namespace meov::definitions
