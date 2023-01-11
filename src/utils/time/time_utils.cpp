#include "utils/time/time_utils.hpp"

namespace meov::utils::time {

void Clock::Update() {
    mEnd = std::move(mBegin);
    mBegin = HRC::now();
    mDelta = mBegin - mEnd;
}

double Clock::Delta() const {
    return ch::duration<double>{ mDelta }.count();
}

ch::nanoseconds Clock::OriginalDelta() const {
    return mDelta;
}


void Stopwatch::Start() {
    mState = State::Running;
    mBegin = HRC::now();
    mEnd = {};
}

void Stopwatch::Stop() {
    mState = State::Stopped;
    mEnd = HRC::now();
    mBegin = {};
}

void Stopwatch::Lap(std::string label) {
    if(label.empty()) {
        label = "Lap " + std::to_string(mLaps.size());
    }
    label = std::to_string(mLaps.size() + 1) + ". " + label;
    mEnd = HRC::now();
    mLaps.emplace(std::move(label), std::move(mEnd - mBegin));
}

void Stopwatch::Reset() {
    mLaps.clear();
    Stop();
}

ch::nanoseconds Stopwatch::CurrentTime() const {
    switch(mState) {
        case State::Idle: return HRC::duration::zero();
        case State::Running: return HRC::now() - mBegin;
        case State::Stopped: return mEnd - mBegin;
        default: return HRC::duration::zero();
    }
}

std::unordered_multimap<std::string, ch::nanoseconds> Stopwatch::Laps() const {
    return mLaps;
}

}  // namespace meov::utils::time