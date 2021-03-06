#include "app_info.hpp"

#define VERSION "v0.2.0"
#define SHADER_VERSION_MAJOR 4
#define SHADER_VERSION_MINOR 5
#define SHADER_VERSION_PATCH 0
#define SHADER_VERSION "#version 450 core"
#define PROGRAM_NAME "MEOV | Minimalistic Easy Object Viewer"

#define LOG_LEVEL "Release"

#define GIT_COMMIT_HASH "e35e6ea36b02bbe7820423d87f0274a5cb4084ef-dirty"
#define GIT_COMMIT_DATE "Tue Jun 7 19:43:19 2022"
#define GIT_COMMIT_MESSAGE "Updated models and changed some default values."

namespace meov {

const std::string AppInfo::Version() {
#if defined(VERSION)
    return VERSION;
#else
    return "ERROR_VERSION_NOT_FOUND";
#endif
}

const std::string AppInfo::GLSLVersion() {
#if defined(SHADER_VERSION)
    return SHADER_VERSION;
#else
    return "#version 330 core";
#endif
}

const size_t AppInfo::GLSLVersionMajor() {
#if defined(SHADER_VERSION_MAJOR)
    return SHADER_VERSION_MAJOR;
#else
    return 3;
#endif
}

const size_t AppInfo::GLSLVersionMinor() {
#if defined(SHADER_VERSION_MINOR)
    return SHADER_VERSION_MINOR;
#else
    return 3;
#endif
}

const size_t AppInfo::GLSLVersionPatch() {
#if defined(SHADER_VERSION_PATCH)
    return SHADER_VERSION_PATCH;
#else
    return 0;
#endif
}

const std::string AppInfo::Name() {
#if defined(PROGRAM_NAME)
    return PROGRAM_NAME;
#else
    return "MEOV | Minimalistic Easy Object Viewer";
#endif
}

const std::string AppInfo::LogLevel() {
#if defined(LOG_LEVEL)
    return LOG_LEVEL;
#else
    return "Debug";
#endif
}

const std::string AppInfo::GitCommitHash() {
#if defined(GIT_COMMIT_HASH)
    return GIT_COMMIT_HASH;
#else
    return "ERROR_GIT_UNAVAILABLE";
#endif
}

const std::string AppInfo::GitCommitDate() {
#if defined(GIT_COMMIT_DATE)
    return GIT_COMMIT_DATE;
#else
    return "ERROR_GIT_UNAVAILABLE";
#endif
}

const std::string AppInfo::GitCommitMessage() {
#if defined(GIT_COMMIT_MESSAGE)
    return GIT_COMMIT_MESSAGE;
#else
    return "ERROR_GIT_UNAVAILABLE";
#endif
}

bool AppInfo::IsDebugMode() {
#if defined(DEBUG)
    return true;
#else
    return false;
#endif
}

}  // namespace meov
