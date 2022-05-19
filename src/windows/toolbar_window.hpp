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

    void setExtensions(const std::string_view ext);

protected:
    void DrawImpl() override final;

private:
    std::string mExtensions{ ".obj,.gltf,.fbx,.stl" };
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
