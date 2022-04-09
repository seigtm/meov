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

constexpr std::string_view GitCommitHash{ "cdd5c2c634590136994c729f6c5d439bd9e75426-dirty" };
constexpr std::string_view GitCommitDate{ "Sat Apr 9 07:45:58 2022" };
constexpr std::string_view GitCommitMessage{ "Some fun with pain. idk just some changes u know" };



} // namespace meov::definitions
