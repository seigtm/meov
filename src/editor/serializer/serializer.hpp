#pragma once

namespace meov::editor::serializer {

class Serializer {
public:
	template<class Type>
	static void serialize(const Type &value) = delete;

	template<> static void serialize<int>(const int &value);
};


} // namespace meov::editor::serializer
