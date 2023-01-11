#pragma once

namespace meov::editor::serializer {

class Serializer {
public:
	template<class Type>
	static void serialize(const Type &value) = delete;
};

template<>
void Serializer::serialize<int>(const int &value) {}

} // namespace meov::editor::serializer
