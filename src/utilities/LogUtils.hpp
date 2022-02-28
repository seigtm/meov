#pragma once

#include "Utilities.hpp"
#include "LogStorage.hpp"

namespace meov::utils {

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

void OpenGLLogCallback(
    GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei len, const GLchar *msg, const void *);

void SDLLogCallback(void *userdata, int category, SDL_LogPriority priority, const char *message);

}  // namespace meov::utils
