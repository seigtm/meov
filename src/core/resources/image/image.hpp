#pragma once

#include <span>
#include <vector>
#include <glm/vec2.hpp>
#include <utils/types.hpp>
#include "core/resources/manager/resource.hpp"

namespace meov::utils::stb {
struct image;
} // namespace meov::utils::stb

namespace meov::core::resources {

class Image : public Resource {
public:
	static constexpr i32 MaxChannelsCount{ 4 };

	Image(std::string &&name, fs::path &&path, std::vector<byte> &&bytes, glm::uvec2 &&size,
		const i32 channels) noexcept;
	Image(const std::string_view name, const fs::path &path, const std::span<byte> &bytes,
		const glm::uvec2 &size, const i32 channels) noexcept;
	Image(const std::string_view name, const utils::stb::image &image);

	[[nodiscard]] bool valid() const noexcept;
	[[nodiscard]] bool empty() const noexcept;
	[[nodiscard]] std::span<const byte> raw() const noexcept;
	[[nodiscard]] u32 length() const noexcept; ///< In bytes
	[[nodiscard]] glm::uvec2 size() const noexcept;
	[[nodiscard]] i32 channels() const noexcept;

	[[nodiscard]] static constexpr bool isValidChannels(const i32 channels) {
		return channels >= 0 && channels <= MaxChannelsCount;
	}
private:
	std::vector<byte> mBytes;
	glm::uvec2 mSize{};
	i32 mChannels{};
};

} // namespace meov::core::resources
