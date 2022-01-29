#pragma once

#include "Common.hpp"
#include "Utilities.hpp"
#include "LogUtils.hpp"
#include "windows/Base.hpp"

namespace MEOV::Window {

class Log final : public Base, public MEOV::Utils::Singleton<Log> {
public:
    Log();
    void Update(std::vector<plog::util::nstring>* messages);

protected:
    void DrawImpl() override final;

private:
    std::vector<plog::util::nstring>* _messages;
};

}  // namespace MEOV::Window
