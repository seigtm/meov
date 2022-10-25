#pragma once

namespace meov::utils {

template<class ConstructorCallback, class DestructorCallback>
class ScopeWrapper {
public:
	ScopeWrapper(ConstructorCallback &&cCallback, DestructorCallback &&dCallback)
		: mDestructorCallback{ std::move(dCallback) } {
		cCallback();
	}
	~ScopeWrapper() {
		mDestructorCallback();
	}

private:
	DestructorCallback mDestructorCallback;
};

} // namespace meov::utils
