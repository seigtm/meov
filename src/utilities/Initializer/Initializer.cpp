#include "Common.hpp"

#include "Initializer.hpp"

namespace meov::utilities {

Initializer::Initializer(Listener *parent, std::string &&name, Task &&onInit, Task &&onDestroy)
	: mParent{ parent }
	, mName{ std::move(name) }
	, mDestroyTask{ std::move(onDestroy) }
{
	LOGI << "Initialize " << mName;
	LogStatus(onInit());
}

Initializer::~Initializer() {
	LOGI << "Destroying " << mName;
	LogStatus(mDestroyTask());
}

void Initializer::LogStatus(bool success) const {
	if (success) {
		LOGI << mName << " was initialized successfly";
		return;
	}
	LOGE << "Failed to initialize " << mName;
	if (mParent) {
		mParent->OnFail(mName);
	}
}

} // namespace meov::utilities
