#include "common.hpp"

#include "event_manager.hpp"

namespace meov::core::managers {

std::vector<std::weak_ptr<MouseManager::Listener>> MouseManager::sListeners{};
std::unordered_map<SDL_Keycode, bool> KeyboardManager::sKeyMap{};

//========================== MouseManager ===========================//

void MouseManager::HandleEvent(SDL_Event &event) {
    if(sListeners.empty())
        return;

    std::function<void(std::shared_ptr<Listener>)> method;
    switch(event.type) {
        case SDL_MOUSEBUTTONDOWN: {
            method = [button = event.button](std::shared_ptr<Listener> listener) {
                listener->OnMousePressed(Convert(button.which), { button.x, button.y });
            };
        } break;
        case SDL_MOUSEBUTTONUP: {
            method = [button = event.button](std::shared_ptr<Listener> listener) {
                listener->OnMouseReleased(Convert(button.which), { button.x, button.y });
            };
        } break;
        case SDL_MOUSEMOTION: {
            method = [motion = event.motion](std::shared_ptr<Listener> listener) {
                listener->OnMouseReleased(Convert(motion.which), { motion.x, motion.y });
            };
        } break;
        case SDL_MOUSEWHEEL: {
            method = [wheel = event.wheel](std::shared_ptr<Listener> listener) {
                const float coef{ wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1.f : 1.f };
                listener->OnMouseScroll({ wheel.preciseX * coef,
                                          wheel.preciseY * coef });
            };
        } break;
        default:
            return;
    }

    for(auto iter = sListeners.begin(); iter != sListeners.end(); ++iter) {
        if(auto listener{ iter->lock() }; listener) {
            method(listener);
        } else {
            iter = sListeners.erase(iter);
            if(iter == sListeners.end()) break;
        }
    }
}

void MouseManager::AddListener(std::weak_ptr<Listener> &&listener) {
    if(!listener.expired())
        sListeners.emplace_back(std::move(listener));
}

void MouseManager::RemoveListener(const std::shared_ptr<Listener> &listener) {
    auto found{
        std::find_if(sListeners.begin(), sListeners.end(), [&listener](std::weak_ptr<Listener> weak) {
            if(auto target{ weak.lock() }; target && target == listener) {
                return true;
            }
            return false;
        })
    };
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

bool KeyboardManager::IsKeyModificatorPressed(SDL_Keymod modificator) {
    return SDL_GetModState() == modificator;
}

bool KeyboardManager::IsMyEvent(SDL_Event &event) {
    return event.type == SDL_KEYUP || event.type == SDL_KEYDOWN;
}


}  // namespace meov::core::managers
