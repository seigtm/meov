#include "AppInfo.hpp"

#define VERSION "v0.1.3"
#define SHADER_VERSION_MAJOR 3
#define SHADER_VERSION_MINOR 3
#define SHADER_VERSION_PATCH 0
#define SHADER_VERSION "#version 330 core"
#define PROGRAM_NAME "MEOV | Minimalistic Easy Object Viewer"

#define LOG_LEVEL "Debug"

#define GIT_COMMIT_HASH "37eac9e0783c35c49b617f3d366f397f77dc4a9a"
#define GIT_COMMIT_DATE "Fri Feb 25 18:45:24 2022"
#define GIT_COMMIT_MESSAGE "Some glass of liquided shit"

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
    return "meov | Minimalistic Easy Object Viewer";
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
