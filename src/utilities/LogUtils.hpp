#pragma once

#include "Utilities.hpp"
#include "LogStorage.hpp"

namespace MEOV::Utils {

class DefaultFormatter {
public:
    static plog::util::nstring header();
    static plog::util::nstring format(const plog::Record& record);
};

class LogUtils : public Singleton<LogUtils> {
public:
    using AppenderPtr = std::unique_ptr<plog::IAppender>;

    void Initialize();
    std::string GenerateLogFileName() const;
    Log::Storage::Ref GetLogStorage() const;

private:
    const std::string sLoggerDirectory{ "logs/" };
    Log::Storage::Ref mLogStorage;
};

}  // namespace MEOV::Utils
