#include "windows/Test.hpp"

namespace MEOV::Window {

Test::Test()
    : Base{ "Test window", ImVec2{ 200, 150 } } {}

void Test::DrawImpl() {
    ImGui::Text("Hello from the test window!");
    if(ImGui::Button("Click me, senpai <3!")) {
        LOGI << "Button was clicked!";
    }
}

}  // namespace MEOV::Window
