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

constexpr std::string_view GitCommitHash{ "181da37cf976c4cb6e10785753cbada84516a83f-dirty" };
constexpr std::string_view GitCommitDate{ "Fri May 27 08:48:44 2022" };
constexpr std::string_view GitCommitMessage{ "I Fix something and add model rendering optimization" };

} // namespace meov::definitions
