#include "selectable.hpp"

namespace meov::core::mixin {

void Selectable::Select() {
    mSelected = true;
}
void Selectable::Deselect() {
    mSelected = false;
}
bool Selectable::IsSelected() const {
    return mSelected;
}

}  // namespace meov::core::mixin
