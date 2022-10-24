#include "common.hpp"

#include "windows/properties/properties_window.hpp"

#include "object.hpp"

namespace meov::Window {

Properties::Properties(ImVec2 const &size, bool isClosable)
    : Base{ "Properties", size, isClosable } {}

void Properties::Select(std::vector<std::weak_ptr<core::Object>> &&object) {
    mObjects = std::move(object);
}

void Properties::Reset() {
    mObjects.clear();
}

void Properties::DrawImpl() {
    for(auto &&weakObj : mObjects) {
        if(auto &&obj{ weakObj.lock() }; obj)
            obj->Serialize();
    }
}

}  // namespace meov::Window
