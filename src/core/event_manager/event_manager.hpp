#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <limits>

#include <SDL_keycode.h>
#include <SDL_events.h>
#include <glm/vec2.hpp>

namespace meov::core::managers {

class MouseManager {
public:
    enum class Button : uint32_t {
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE,
        Right = SDL_BUTTON_RIGHT,
        X1 = SDL_BUTTON_X1,
        X2 = SDL_BUTTON_X2,
        None = UINT_MAX
    };

    class Listener {
    public:
        virtual void OnMousePressed(Button button, const glm::vec2 &position){};
        virtual void OnMouseReleased(Button button, const glm::vec2 &position){};
        virtual void OnMouseMove(Button button, const glm::vec2 &position){};
        virtual void OnMouseScroll(const glm::vec2 &direction){};
    };

    static void HandleEvent(SDL_Event &event);
    static void AddListener(std::weak_ptr<Listener> &&listener);
    static void RemoveListener(const std::shared_ptr<Listener> &listener);

private:
    static std::vector<std::weak_ptr<Listener>> sListeners;

    static Button Convert(uint32_t button);
};

class KeyboardManager {
public:
    static void HandleEvent(SDL_Event &event);

    static bool IsKeyPressed(SDL_Keycode);
    static bool IsAnyKeyPressed(std::initializer_list<SDL_Keycode> &&keys);
    static bool IsKeyModificatorPressed(SDL_Keymod);

    static bool IsMyEvent(SDL_Event &event);

private:
    static std::unordered_map<SDL_Keycode, bool> sKeyMap;
};

}  // namespace meov::core::managers
