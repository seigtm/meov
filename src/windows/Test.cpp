#include "windows/Test.hpp"

namespace MEOV::Window {

Test::Test()
    : Base{ "Test window", ImVec2{ 400, 800 } } {}

Test::~Test() {}

void Test::DrawImpl() {
    ImGui::Text("Hello from the test window!");
    ImGui::Button("Click me, senpai <3!");
}

}  // namespace MEOV::Window
