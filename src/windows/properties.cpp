#include "windows/properties.hpp"

#include "object.hpp"
#include "common.hpp"

namespace meov::Window {

Properties::Properties(ImVec2 const &size, bool isClosable)
    : Base{ "Properties", size, isClosable } {}

void Properties::Select(std::weak_ptr<core::Object> &&object) {
    mObject = std::move(object);
}

void Properties::Reset() {
    mObject.reset();
}

void Properties::DrawImpl() {
    if(auto &&obj{ mObject.lock() }; obj)
        obj->Serialize();
}

}  // namespace meov::Window