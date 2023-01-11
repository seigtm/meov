#include <common>
#include <core/core.hpp>
#include <app_info/app_info.hpp>

#if defined(MEOV_WITH_EDITOR)
#include <editor/editor.hpp>
#endif

int main() {
    if constexpr (meov::AppInfo::WithEditor()) {
        return meov::editor::make<meov::core::Core>().run();
    }

    return meov::core::Core{}.Run();
}
