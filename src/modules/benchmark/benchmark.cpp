#include <fstream>
#include <filesystem>
#include "benchmark/benchmark.hpp"

namespace meov::modules {

std::string Benchmark::sOutputPath{ Benchmark::DefaultOutputPath };

Benchmark::Benchmark(const std::string_view function_name, const std::string_view name) noexcept
	: mFunctionName{ function_name }
	, mName{ name.empty() ? DefaultName : name }
	, mStart{ std::chrono::steady_clock::now() } {}

Benchmark::~Benchmark() {
	const auto result{ str() };
	if (!std::filesystem::exists(sOutputPath)) {
		std::filesystem::create_directories(sOutputPath);
	}
	const auto filename{ sOutputPath + functionNameToFilename(mFunctionName) };
	if (std::ofstream file{ filename, std::ios_base::app }; file.is_open()) {
		file << result << "\n";
	}
}

std::string Benchmark::str() const noexcept {
	const auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::steady_clock::now() - mStart
	).count();

	return std::string{ mFunctionName }.append(Delimiter).append(mName)
		.append(Delimiter).append(std::to_string(elapsed_time))
		.append(Delimiter).append("microseconds");
}

void Benchmark::setOutputPath(const std::string_view output_path) noexcept {
	sOutputPath = output_path;
}

std::string Benchmark::functionNameToFilename(std::string_view function_name) noexcept {
	if (const auto last_sep{ function_name.find_last_of("::") }; last_sep != std::string_view::npos) {
		function_name.remove_prefix(last_sep + 1);
	}
	return std::string{ function_name } + ".csv";
}

} // namespace meov::modules