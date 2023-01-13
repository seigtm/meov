#include <utils/stb/image.hpp>

#include "core/resources/image/image.hpp"

namespace meov::core::resources {

Image::Image(std::string &&name, fs::path &&path, std::vector<byte> &&bytes, glm::uvec2 &&size,
	const i32 channels) noexcept
	: Resource{ std::move(name), std::move(path) }
	, mBytes{ std::move(bytes) }
	, mSize{ std::move(size) }
	, mChannels{ channels }
{}

Image::Image(const std::string_view name, const fs::path &path, const std::span<byte> &bytes,
	const glm::uvec2 &size, const i32 channels) noexcept
	: Resource{ std::string{ name }, path }
	, mBytes{ bytes.begin(), bytes.end() }
	, mSize{ size }
	, mChannels{ channels }
{}

Image::Image(const std::string_view name, const utils::stb::image &image)
	: Resource{ std::string{ name }, fs::path{ image.filename } }
	, mBytes{ image.bytes, image.bytes + image.length() }
	, mSize{ image.width, image.height }
	, mChannels{ image.channels }
{}

bool Image::valid() const noexcept {
	return !mBytes.empty() && mSize.x != 0 && mSize.y != 0 && isValidChannels(mChannels);
}
bool Image::empty() const noexcept {
	return mBytes.empty();
}
std::span<const byte> Image::raw() const noexcept {
	return std::span{ mBytes };
}
u32 Image::length() const noexcept {
	return mBytes.size();
}
glm::uvec2 Image::size() const noexcept {
	return mSize;
}
i32 Image::channels() const noexcept {
	return mChannels;
}



} // namespace meov::core::resources
