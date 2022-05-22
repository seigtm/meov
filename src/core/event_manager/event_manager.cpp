#include "common.hpp"

#include "event_manager.hpp"

namespace meov::core::managers {

std::vector<MouseManager::Listener *> MouseManager::sListeners{};
std::unordered_map<SDL_Keycode, bool> KeyboardManager::sKeyMap{};

//========================== MouseManager ===========================//

void MouseManager::HandleEvent(SDL_Event &event) {
    if(sListeners.empty())
        return;

    std::function<void(Listener &)> method;
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN: {
            method = [button = event.button](Listener &listener) {
                listener.OnMousePressed(Convert(button.button), { button.x, button.y });
            };
        } break;
        case SDL_MOUSEBUTTONUP: {
            method = [button = event.button](Listener &listener) {
                listener.OnMouseReleased(Convert(button.button), { button.x, button.y });
            };
        } break;
        case SDL_MOUSEMOTION: {
            method = [motion = event.motion](Listener &listener) {
                listener.OnMouseMove({ motion.x, motion.y });
            };
        } break;
        case SDL_MOUSEWHEEL: {
            method = [wheel = event.wheel](Listener &listener) {
                const float coef{ wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1.f : 1.f };
                listener.OnMouseScroll({ wheel.preciseX * coef,
                                         wheel.preciseY * coef });
            };
        } break;
        default:
            return;
    }

    for(auto iter = sListeners.begin(); iter != sListeners.end(); ++iter) {
        if(Listener * listener{ *iter }; listener) {
            method(*listener);
        } else {
            iter = sListeners.erase(iter);
            if(iter == sListeners.end()) break;
        }
    }
}

void MouseManager::AddListener(Listener *listener) {
    if(listener != nullptr)
        sListeners.emplace_back(listener);
}

void MouseManager::RemoveListener(const Listener *listener) {
    auto found{ std::find(sListeners.begin(), sListeners.end(), listener) };
    if(found != sListeners.end())
        sListeners.erase(found);
}

MouseManager::Button MouseManager::Convert(uint32_t button) {
    return button >= SDL_BUTTON_LEFT && button <= SDL_BUTTON_X2 ? Button{ button } : Button::None;
}

//========================= KeyboardManager =========================//

void KeyboardManager::HandleEvent(SDL_Event &event) {
    if(!IsMyEvent(event))
        return;

    sKeyMap[event.key.keysym.sym] = event.key.state;
}

bool KeyboardManager::IsKeyPressed(SDL_Keycode code) {
    return sKeyMap[code];
}

bool KeyboardManager::IsAnyKeyPressed(std::initializer_list<SDL_Keycode> &&keys) {
    return std::any_of(keys.begin(), keys.end(), [](SDL_Keycode key) { return IsKeyPressed(key); });
}

bool KeyboardManager::IsKeyModificatorPressed(SDL_Keymod modificator) {
    return SDL_GetModState() == modificator;
}

bool KeyboardManager::IsMyEvent(SDL_Event &event) {
    return event.type == SDL_KEYUP || event.type == SDL_KEYDOWN;
}


}  // namespace meov::core::managers
