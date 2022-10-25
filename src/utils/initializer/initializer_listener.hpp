#pragma once

#include <string_view>

namespace meov::utilities {

class InitializerListener {
public:
	virtual ~InitializerListener() = default;
	virtual void OnFail(const std::string_view &taskName) = 0;
};

} // namespace meov::utilities
