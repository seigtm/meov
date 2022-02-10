#include "windows/Test.hpp"

namespace MEOV::Window {

Test::Test()
    : Base{ "Test window", ImVec2{ 200, 150 } } {}

void Test::DrawImpl() {
    ImGui::Text("Hello from the test window!");
    if(ImGui::Button("Log 100 times o___o!")) {
        // FIXME: Erase this pseudo-benchmarking later on.
        auto start = std::chrono::steady_clock::now();
        for(unsigned int i{}; i < 100; ++i)
            LOGI << "Button was clicked! [times = " << i << "]";
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        LOGI << "Duration: " << duration << "ms.\n";
    }
}

}  // namespace MEOV::Window
