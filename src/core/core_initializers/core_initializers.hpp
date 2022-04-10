#pragma once

#include <string>
#include <memory>

#include "initializer.hpp"

namespace meov::core::initializers {

std::unique_ptr<utilities::Initializer> MakeSDLInitializer(
    utilities::Initializer::Listener *parent);

std::unique_ptr<utilities::Initializer> MakeSDLWindowInitializer(
    utilities::Initializer::Listener *parent,
    SDL_Window *&window, SDL_GLContext &ctx);

std::unique_ptr<utilities::Initializer> MakeOpenGLInitializer(
    utilities::Initializer::Listener *parent);

std::unique_ptr<utilities::Initializer> MakeImGuiInitializer(
    utilities::Initializer::Listener *parent,
    SDL_Window *&window, SDL_GLContext &ctx);

}  // namespace meov::core::initializers