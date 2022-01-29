#pragma once

#include "Common.hpp"
#include "Utilities.hpp"
#include "windows/Log.hpp"

namespace MEOV::Utils {

class DefaultFormatter {
public:
    static plog::util::nstring header();
    static plog::util::nstring format(const plog::Record& record);
};

class Log : public Singleton<Log> {
public:
    using AppenderPtr = std::unique_ptr<plog::IAppender>;

    void Initialize();
    std::string GenerateLogFileName() const;

private:
    const std::string sLoggerDirectory{ "logs/" };
};

}  // namespace MEOV::Utils

namespace plog {

template<class Formatter>
class LogWindowAppender final : public IAppender {
public:
    LogWindowAppender();
    void write(const Record& record) override final;

private:
    std::vector<util::nstring> mMessages;
};

}  // namespace plog
