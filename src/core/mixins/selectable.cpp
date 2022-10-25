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

void Selectable::SetSelect(bool selected) {
    mSelected = selected;
}

}  // namespace meov::core::mixin
