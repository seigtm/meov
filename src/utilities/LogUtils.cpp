#include "Common.hpp"
#include "AppInfo.hpp"
#include "LogUtils.hpp"

#include <plog/Init.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Record.h>

#include <sstream>

namespace putil = plog::util;

namespace {

putil::nstring str2nstr(const std::string &str) {
    return std::wstring_convert<std::codecvt_utf8<putil::nchar>>().from_bytes(str);
}

}  // namespace

namespace meov::Utils {

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
    ss << beg << record.getFunc() << PLOG_NSTR("@") << record.getLine() << end << PLOG_NSTR(' ');
    ss << record.getMessage() << PLOG_NSTR("\n");

    return ss.str();
}

void LogUtils::Initialize() {
    if(!fs::exists(sLoggerDirectory)) {
        fs::create_directories(sLoggerDirectory);
    }

    const std::string logfile{ sLoggerDirectory + GenerateLogFileName() };

    static plog::ColorConsoleAppender<DefaultFormatter> Console;
    static plog::RollingFileAppender<DefaultFormatter> File{ logfile.c_str() };
    static meov::Utils::Log::Storage::Ref Storage{ new meov::Utils::Log::Storage };
    mLogStorage = Storage;

    plog::Severity level{ AppInfo::IsDebugMode() ? plog::debug : plog::info };

    plog::init(plog::debug, &File)
#if defined(DEBUG)
        .addAppender(&Console)
#endif
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

}  // namespace meov::Utils
