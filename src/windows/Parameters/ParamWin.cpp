#include "Common.hpp"

#include "ParamWin.hpp"

namespace meov::Window {

Value::Value(const std::string &name, bool readOnly)
    : mTitle{ name }, mReadOnly{ readOnly } {}

Value::Value(std::string &&name, bool readOnly)
    : mTitle{ std::move(name) }, mReadOnly{ readOnly } {}

const std::string &Value::GetTitle() const {
    return mTitle;
}

Parameters::Parameters(const std::string_view &title, const ImVec2 &size)
    : Base{ title, size } {}

Parameters &Parameters::Add(const Value::Shared &value) {
    mValues.push_back(value);
    return *this;
}

void Parameters::DrawImpl() {
    for(auto &&value : mValues) {
        if(value == nullptr) continue;
        ImGui::Text(value->GetTitle().c_str());
        value->Draw();
        ImGui::NewLine();
    }
}

}  // namespace meov::Window