#pragma once

#include <chrono>
#include <list>
#include <string>
#include <unordered_map>
#include <functional>
#include <list>
#include <thread>

namespace meov::utilities::time {

namespace ch = std::chrono;
using HRC = ch::high_resolution_clock;

class Clock {
public:
	void Update();

	double Delta() const;
	ch::nanoseconds OriginalDelta() const;

private:
	HRC::time_point mBegin{ HRC::now() };
	HRC::time_point mEnd{ HRC::now() };
	ch::nanoseconds mDelta{};
};

class Stopwatch {
public:
	void Start();
	void Stop();
	void Lap(std::string label = {});
	void Reset();

	ch::nanoseconds CurrentTime() const;
	std::unordered_multimap<std::string, ch::nanoseconds> Laps() const;

private:
	enum class State : unsigned char {
		Idle = 'i',
		Running = 'r',
		Stopped = 's'
	};

	State mState{ State::Idle };
	HRC::time_point mBegin{ HRC::now() };
	HRC::time_point mEnd{ HRC::now() };
	std::unordered_multimap<std::string, ch::nanoseconds> mLaps;
};

} // namespace meov::utilities::time