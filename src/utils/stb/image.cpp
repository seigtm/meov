#include <stb_image.h>

#include "utils/stb/image.hpp"

namespace meov::utils::stb {

image::image(const std::string_view filename)
	: bytes{ !filename.empty() ? stbi_load(filename.data(), &width, &height, &channels, 0) : nullptr }
	, wasLoaded{ bytes != nullptr }
	, filename{ filename } { }

image::~image() {
	if (wasLoaded) {
		stbi_image_free(bytes);
	}
}

std::span<const byte> image::raw() const {
	return std::span<const byte>{ bytes, static_cast<size_t>(length()) };
}

u64 image::length() const {
	if (width < 0 || height < 0) return 0;
	return static_cast<u64>(width) * static_cast<u64>(height);
}

bool image::operator==(const image &other) const {
	return width == other.width && height == other.height && channels == other.channels;
}

image::image(image &&other) noexcept
	: width{ other.width }, height{ other.height }, channels{ other.channels }
	, bytes{ other.bytes }, wasLoaded{ other.wasLoaded } {
	other.width = 0;
	other.height = 0;
	other.channels = 0;
	other.bytes = nullptr;
	other.wasLoaded = false;
}
image& image::operator=(image &&other) noexcept {
	if (this == &other) return *this;

	if (wasLoaded) stbi_image_free(bytes);

	width = other.width;
	height = other.height;
	channels = other.channels;
	bytes = other.bytes;
	wasLoaded = other.wasLoaded;

	other.width = 0;
	other.height = 0;
	other.channels = 0;
	other.bytes = nullptr;
	other.wasLoaded = false;

	return *this;
}



} // namespace meov::utils::stb
