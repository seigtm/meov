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

constexpr std::string_view GitCommitHash{ "afca1f88807b4ba88aba6b78cd8a1fd2d44bbcfc" };
constexpr std::string_view GitCommitDate{ "Sat Apr 9 11:35:00 2022" };
constexpr std::string_view GitCommitMessage{ "Removed another duplicated directory created by accident." };

} // namespace meov::definitions
