#include "common.hpp"
#include "app_info.hpp"
#include "log_utils.hpp"

#include <plog/Init.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Record.h>

#include <sstream>

namespace putil = plog::util;

namespace {

putil::nstring str2nstr(const std::string &str) {
    return std::wstring_convert<std::codecvt_utf8<putil::nchar>>().from_bytes(str);
}

}  // namespace

namespace meov::utils {

putil::nstring DefaultFormatter::header() {
    putil::nostringstream out;
    const size_t offset{ 1 };
    size_t max_width{ 80 };
    if(static_cast<long>(AppInfo::Name().size()) % 2 != 0) ++max_width;
    const putil::nchar stroffset{ PLOG_NSTR(' ') };

    auto put{ [&](const putil::nstring &left, const putil::nstring &right) {
        size_t half{ (max_width - (right.size() + offset)) / 2 };
        out << std::setfill(PLOG_NSTR(' ')) << std::setw(max_width - (right.size() + offset)) << std::left
            << stroffset + left << std::right << right << "\n";
    } };

    const putil::nstring title{ str2nstr(AppInfo::Name()) + PLOG_NSTR(" log") };
    out << std::setfill(PLOG_NSTR('=')) << std::setw((max_width - (title.size())) / 2) << std::right
        << stroffset << title << stroffset << std::setw((max_width - (title.size())) / 2) << PLOG_NSTR("\n");

    // clang-format off
    put(PLOG_NSTR("Name:"),         str2nstr(AppInfo::Name()));
    put(PLOG_NSTR("Version:"),      str2nstr(AppInfo::Version()));
    put(PLOG_NSTR("Log level:"),    str2nstr(AppInfo::LogLevel()));
    put(PLOG_NSTR("GLSL Version:"), str2nstr(AppInfo::GLSLVersion()));
    put(PLOG_NSTR("Git hash:"),     str2nstr(AppInfo::GitCommitHash()));
    put(PLOG_NSTR("Git date:"),     str2nstr(AppInfo::GitCommitDate()));
    put(PLOG_NSTR("Git message:"),  str2nstr(AppInfo::GitCommitMessage()));
    // clang-format on

    out << putil::nstring(max_width, PLOG_NSTR('=')) << '\n';

    return out.str();
}

putil::nstring DefaultFormatter::format(const plog::Record &record) {
    tm t;
    putil::localtime_s(&t, &record.getTime().time);
    constexpr putil::nchar beg{ PLOG_NSTR('[') };
    constexpr putil::nchar end{ PLOG_NSTR(']') };

    putil::nostringstream ss;
    ss << beg << t.tm_year + 1900 << "." << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << "." << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << end;
    ss << beg << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".") << std::setfill(PLOG_NSTR('0')) << std::setw(3) << record.getTime().millitm << end;
    ss << beg << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << end;
    ss << PLOG_NSTR(' ') << record.getMessage();
    ss << PLOG_NSTR("\t\t") << beg << "file: " << record.getFunc() << PLOG_NSTR(" at ") << record.getLine() << end;
    ss << PLOG_NSTR("\n");

    return ss.str();
}

void LogUtils::Initialize() {
    if(!fs::exists(sLoggerDirectory)) {
        fs::create_directories(sLoggerDirectory);
    }

    const std::string logfile{ sLoggerDirectory + GenerateLogFileName() };

    static plog::ColorConsoleAppender<DefaultFormatter> Console;
    static plog::RollingFileAppender<DefaultFormatter> File{ logfile.c_str() };
    static meov::utils::Log::Storage::Ref Storage{ new meov::utils::Log::Storage };
    mLogStorage = Storage;

    plog::Severity level{ AppInfo::IsDebugMode() ? plog::debug : plog::info };

    plog::init(plog::debug, &File)
        // #if defined(DEBUG)
        .addAppender(&Console)
        // #endif
        .addAppender(&*mLogStorage);
}

std::string LogUtils::GenerateLogFileName() const {
    time_t now{ time(nullptr) };
    std::stringstream out;
    out << std::put_time(localtime(&now), "%y%m%d%H.log");
    return out.str();
}

Log::Storage::Ref LogUtils::GetLogStorage() const {
    return mLogStorage;
}

void OpenGLLogCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                       GLsizei, const GLchar *msg, const void *) {
    static const auto toStr{ [](const GLenum e) {
        switch(e) {
            case GL_DEBUG_SOURCE_API: return "[API] ";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "[Window system] ";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "[Shader compiler] ";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "[Third party] ";
            case GL_DEBUG_SOURCE_APPLICATION: return "[Application] ";
            case GL_DEBUG_SOURCE_OTHER: return "[Other source] ";

            case GL_DEBUG_TYPE_ERROR: return "[Error] ";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "[Deprecated behavior] ";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "[Undefined behavior] ";
            case GL_DEBUG_TYPE_PORTABILITY: return "[Portability] ";
            case GL_DEBUG_TYPE_PERFORMANCE: return "[Performance] ";
            case GL_DEBUG_TYPE_MARKER: return "[Marker] ";
            case GL_DEBUG_TYPE_OTHER: return "[Other type] ";

            default: return "[Unknown] ";
        }
    } };
    static const auto level{ [severity] {
        switch(severity) {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return plog::debug;
            case GL_DEBUG_SEVERITY_LOW: return plog::info;
            case GL_DEBUG_SEVERITY_MEDIUM: return plog::warning;
            case GL_DEBUG_SEVERITY_HIGH: return plog::error;
            default: return plog::none;
        }
    } };

    LOG(level()) << toStr(source) << toStr(type) << " " << id << ": " << msg;
}

void SDLLogCallback(void *, int category, SDL_LogPriority priority, const char *message) {
    static const auto toStr{ [](const int category) {
        switch(category) {
            case SDL_LOG_CATEGORY_APPLICATION: return "[Application] ";
            case SDL_LOG_CATEGORY_ERROR: return "[Error] ";
            case SDL_LOG_CATEGORY_ASSERT: return "[Assert] ";
            case SDL_LOG_CATEGORY_SYSTEM: return "[System] ";
            case SDL_LOG_CATEGORY_AUDIO: return "[Audio] ";
            case SDL_LOG_CATEGORY_VIDEO: return "[Video] ";
            case SDL_LOG_CATEGORY_RENDER: return "[Render] ";
            case SDL_LOG_CATEGORY_INPUT: return "[Input] ";
            case SDL_LOG_CATEGORY_TEST: return "[Test] ";

            default: return "Unknown";
        }
    } };

    static const auto level{ [priority] {
        switch(priority) {
            case SDL_LOG_PRIORITY_VERBOSE: return plog::verbose;
            case SDL_LOG_PRIORITY_DEBUG: return plog::debug;
            case SDL_LOG_PRIORITY_INFO: return plog::info;
            case SDL_LOG_PRIORITY_WARN: return plog::warning;
            case SDL_LOG_PRIORITY_ERROR: return plog::error;
            case SDL_LOG_PRIORITY_CRITICAL: return plog::fatal;
            default: return plog::none;
        }
    } };

    LOG(level()) << toStr(category) << message;
}

}  // namespace meov::utils
