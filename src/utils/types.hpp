#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace meov {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
using f64 = double;
using f128 = long double;

using byte = u8;

template<class T, class Deleter = std::default_delete<T>>
using uptr = std::unique_ptr<T, Deleter>;

template<class T>
using sptr = std::shared_ptr<T>;

template<class T>
using wptr = std::weak_ptr<T>;

template<class Key, class T, class Hasher = std::hash<Key>, class KeyEq = std::equal_to<Key>,
	class Alloc = std::allocator<std::pair<const Key, T>>>
using umap = std::unordered_map<Key, T, Hasher, KeyEq, Alloc>;

} // namespace meov
