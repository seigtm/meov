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

constexpr std::string_view GitCommitHash{ "85f096ded17ede45fdaadce5045eaaff23dbd818-dirty" };
constexpr std::string_view GitCommitDate{ "Fri Apr 8 10:13:10 2022" };
constexpr std::string_view GitCommitMessage{ "eriohaiohsdhjk;asdfoasdfghjkl" };



} // namespace meov::definitions
