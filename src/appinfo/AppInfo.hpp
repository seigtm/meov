#pragma once

#include <string>

namespace MEOV {

struct AppInfo {
    static const std::string Version();

    static const std::string GLSLVersion();

    static const size_t GLSLVersionMajor();
    static const size_t GLSLVersionMinor();
    static const size_t GLSLVersionPatch();

    static const std::string Name();

    static const std::string GitCommitHash();
    static const std::string GitCommitDate();
    static const std::string GitCommitMessage();
};


}  // namespace MEOV