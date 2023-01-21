#pragma once

#include <string_view>
#include <source_location>
#include <chrono>

namespace meov::modules {

class Benchmark {
public:
	static constexpr std::string_view Delimiter{ "," };
	static constexpr std::string_view DefaultOutputPath{ "benchmark/" };
	static constexpr std::string_view DefaultName{ "<unnamed>" };

	explicit Benchmark(const std::string_view function_name, const std::string_view name) noexcept;
	~Benchmark();

	[[nodiscard]] std::string str() const noexcept;

	Benchmark(const Benchmark&) = delete;
	Benchmark& operator=(const Benchmark&) = delete;
	Benchmark(Benchmark&&) = delete;
	Benchmark& operator=(Benchmark&&) = delete;

	static void setOutputPath(const std::string_view output_path) noexcept;

private:
	const std::string_view mFunctionName;
	const std::string mName;
	std::chrono::steady_clock::time_point mStart;

	static std::string sOutputPath;

	static std::string functionNameToFilename(std::string_view function_name) noexcept;
};

} // namespace meov::modules

#define MEOV_BENCHMARK_BEGIN(name) meov::modules::Benchmark benchmark##__COUNTER__{ __FUNCTION__, name }
#define MEOV_BENCHMARK_END benchmark##__COUNTER__.str()

/*

Interface:
void some_function() {
	MEOV_BENCHMARK_BEGIN;
	// some code here
	const atuo str = MEOV_BENCHMARK_END;
	// store it somewhere
}



*/
