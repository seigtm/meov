#include <common>

#include "editor/serializer/serializer.hpp"

namespace meov::editor::serializer {

template<>
void Serializer::serialize<int>(const int &value) {
}

} // namespace meov::editor::serializer

