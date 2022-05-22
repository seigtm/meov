#define SDL_MAIN_HANDLED

#include "common.hpp"
#include "core.hpp"

int main(int argc, char *argv[]) {
    return meov::core::Core{ std::vector<std::string>{ argv, argv + argc } }.Run();
}
