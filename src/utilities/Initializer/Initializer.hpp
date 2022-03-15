#pragma once

#include <functional>
#include <string>
#include <set>

namespace meov::utilities {

class Initializer final {
public:
	using Shared = std::shared_ptr<Initializer>;
	using Task = std::function<bool()>;

	class Listener {
	public:
		virtual ~Listener() = default;
		virtual void OnFail(const std::string_view &taskName) = 0;
	};

	Initializer(Listener *parent, std::string &&name, Task &&onInit, Task &&onDestroy);
	~Initializer();

private:
	Listener *mParent;
	std::string mName;
	Task mDestroyTask;

	void LogStatus(bool success,
		const std::string_view successMessage,
		const std::string_view failedMessage) const;
};

} // namespace meov::utilities