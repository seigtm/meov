#pragma once

#include <span>
#include "utils/types.hpp"

namespace meov::utils::stb {

struct image {
	i32 width{};
	i32 height{};
	i32 channels{};
	byte *bytes{ nullptr };
	bool wasLoaded{ false };
	std::string filename{};

	image() = default;
	explicit image(const std::string_view filename);
	~image();

	[[nodiscard]] std::span<const byte> raw() const;
	[[nodiscard]] u64 length() const;

 	[[nodiscard]] bool operator==(const image &other) const;

	image(const image &other) = delete;
	image& operator=(const image &other) = delete;

	image(image &&other) noexcept;
	image& operator=(image &&other) noexcept;
};



} // namespace meov::utils::stb
