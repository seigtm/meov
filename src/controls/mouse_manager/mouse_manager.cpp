#include "Common.hpp"
#include "mouse_manager.h"

namespace meov::controls::mouse {

Manager *Manager::Instance() {
    static Manager manager;
    return &manager;
}

} // namespace meov::controls::mouse