#pragma once

namespace meov::core::mixin {

class Selectable {
public:
    void Select();
    void Deselect();
    bool IsSelected() const;
    void SetSelect(bool selected);

private:
    bool mSelected{ false };
};

}  // namespace meov::core::mixin
