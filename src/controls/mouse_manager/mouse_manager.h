#pragma once

#include <glm/common.hpp>

namespace meov::controls::mouse {

struct WheelEventData {
    glm::vec2 mPosition{};
    glm::vec2 mPrecisePosition{};
};

struct ButtonEventData {
    enum class State{
        Pressed, Released
    };
    uint8_t mClicks{};
    glm::vec2 mPosition{};
    State mState{ State::Released };
};

class Listener;

class Manager {
public:
    static Manager *Instance();

    void OnMouseDown(const ButtonEventData &data);
    void OnMouseUp(const ButtonEventData &data);
    void OnMouseMove(const ButtonEventData &data);
    void OnMouseWheel(const WheelEventData &data);

    void Subscribe(Listener *listener);
    void Unsubscribe(Listener *listener);

    ButtonEventData GetLastButtonEventData();
private:
    std::list<Listener *> mListeners;

    ButtonEventData mLastButtonEventData;
    WheelEventData mLastWheelEventData;
};

class Listener {
public:
    static Manager *GetMouseManager();

    virtual void OnMouseButtonDown(const ButtonEventData &) {};
    virtual void OnMouseButtonUp(const ButtonEventData &) {};
    virtual void OnMouseMove(const ButtonEventData &) {};
    virtual void OnMouseWheel(const WheelEventData &) {};
};

}  // namespace meov::controls::mouse