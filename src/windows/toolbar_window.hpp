#pragma once

#include "common.hpp"
#include "windows/base_window.hpp"
#include "model.hpp"

namespace meov::Window {

class ToolBar final : public Base {
public:
    explicit ToolBar(std::shared_ptr<meov::core::Model> &model,
                     bool &done,
                     bool &showLog,
                     bool &showGit,
                     bool &showCamera,
                     bool &showScene,
                     bool &showLightning);

protected:
    void DrawImpl() override final;

private:
    // FIXME: Ultra cringy.
    std::shared_ptr<meov::core::Model> *mModelPointer;
    bool *mDone;
    bool *mShowLog;
    bool *mShowGit;
    bool *mShowCamera;
    bool *mShowScene;
    bool *mShowLightning;
};

}  // namespace meov::Window
