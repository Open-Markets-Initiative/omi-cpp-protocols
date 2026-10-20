#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <string_view>

#include "Decimal.hpp"
#include "Errors.hpp"

// The wire codec every generated decode and encode is written against. Integers
// are read with memcpy and swapped to host order, so unaligned data is fine on
// every target. Nothing here knows any protocol.
namespace iex::iexequities::deep::snap::v1_6::wire {

inline void require(std::string_view what, std::size_t needed, std::size_t available) {
    if (available < needed) { throw DecodeError(what, needed, available); }
}

inline void require_capacity(std::string_view what, std::size_t needed, std::size_t capacity) {
    if (capacity < needed) { throw EncodeError(what, needed, capacity); }
}

constexpr bool little_host = std::endian::native == std::endian::little;

inline std::uint16_t swap(std::uint16_t value) {
    return static_cast<std::uint16_t>((value << 8) | (value >> 8));
}

inline std::uint32_t swap(std::uint32_t value) {
    return (value << 24) | ((value << 8) & 0x00FF0000u) | ((value >> 8) & 0x0000FF00u) | (value >> 24);
}

inline std::uint64_t swap(std::uint64_t value) {
    return (static_cast<std::uint64_t>(swap(static_cast<std::uint32_t>(value))) << 32)
         | swap(static_cast<std::uint32_t>(value >> 32));
}

template <typename T>
inline T load(const std::byte* data) {
    T value;
    std::memcpy(&value, data, sizeof value);
    return value;
}

template <typename T>
inline void store(std::byte* data, T value) {
    std::memcpy(data, &value, sizeof value);
}

// reads

inline std::uint8_t read_u8(const std::byte* data) { return std::to_integer<std::uint8_t>(*data); }
inline std::int8_t read_i8(const std::byte* data) { return static_cast<std::int8_t>(read_u8(data)); }
inline char read_char(const std::byte* data) { return static_cast<char>(*data); }

inline std::uint16_t read_u16_be(const std::byte* data) { const auto value = load<std::uint16_t>(data); return little_host ? swap(value) : value; }
inline std::uint16_t read_u16_le(const std::byte* data) { const auto value = load<std::uint16_t>(data); return little_host ? value : swap(value); }
inline std::uint32_t read_u32_be(const std::byte* data) { const auto value = load<std::uint32_t>(data); return little_host ? swap(value) : value; }
inline std::uint32_t read_u32_le(const std::byte* data) { const auto value = load<std::uint32_t>(data); return little_host ? value : swap(value); }
inline std::uint64_t read_u64_be(const std::byte* data) { const auto value = load<std::uint64_t>(data); return little_host ? swap(value) : value; }
inline std::uint64_t read_u64_le(const std::byte* data) { const auto value = load<std::uint64_t>(data); return little_host ? value : swap(value); }

inline std::int16_t read_i16_be(const std::byte* data) { return static_cast<std::int16_t>(read_u16_be(data)); }
inline std::int16_t read_i16_le(const std::byte* data) { return static_cast<std::int16_t>(read_u16_le(data)); }
inline std::int32_t read_i32_be(const std::byte* data) { return static_cast<std::int32_t>(read_u32_be(data)); }
inline std::int32_t read_i32_le(const std::byte* data) { return static_cast<std::int32_t>(read_u32_le(data)); }
inline std::int64_t read_i64_be(const std::byte* data) { return static_cast<std::int64_t>(read_u64_be(data)); }
inline std::int64_t read_i64_le(const std::byte* data) { return static_cast<std::int64_t>(read_u64_le(data)); }

inline std::uint32_t read_u24_be(const std::byte* data) {
    std::uint32_t value = 0;
    for (std::size_t index = 0; index < 3; ++index) { value = (value << 8) | std::to_integer<std::uint32_t>(data[index]); }
    return value;
}

inline std::uint32_t read_u24_le(const std::byte* data) {
    std::uint32_t value = 0;
    for (std::size_t index = 3; index > 0; --index) { value = (value << 8) | std::to_integer<std::uint32_t>(data[index - 1]); }
    return value;
}

inline std::int32_t read_i24_be(const std::byte* data) { return static_cast<std::int32_t>(read_u24_be(data) << 8) >> 8; }
inline std::int32_t read_i24_le(const std::byte* data) { return static_cast<std::int32_t>(read_u24_le(data) << 8) >> 8; }

inline std::uint64_t read_u48_be(const std::byte* data) {
    std::uint64_t value = 0;
    for (std::size_t index = 0; index < 6; ++index) { value = (value << 8) | std::to_integer<std::uint64_t>(data[index]); }
    return value;
}

inline std::uint64_t read_u48_le(const std::byte* data) {
    std::uint64_t value = 0;
    for (std::size_t index = 6; index > 0; --index) { value = (value << 8) | std::to_integer<std::uint64_t>(data[index - 1]); }
    return value;
}

inline std::int64_t read_i48_be(const std::byte* data) { return static_cast<std::int64_t>(read_u48_be(data) << 16) >> 16; }
inline std::int64_t read_i48_le(const std::byte* data) { return static_cast<std::int64_t>(read_u48_le(data) << 16) >> 16; }

inline float read_f32_be(const std::byte* data) { return std::bit_cast<float>(read_u32_be(data)); }
inline float read_f32_le(const std::byte* data) { return std::bit_cast<float>(read_u32_le(data)); }
inline double read_f64_be(const std::byte* data) { return std::bit_cast<double>(read_u64_be(data)); }
inline double read_f64_le(const std::byte* data) { return std::bit_cast<double>(read_u64_le(data)); }

// writes

inline void write_u8(std::byte* data, std::uint8_t value) { *data = std::byte{ value }; }
inline void write_i8(std::byte* data, std::int8_t value) { write_u8(data, static_cast<std::uint8_t>(value)); }
inline void write_char(std::byte* data, char value) { *data = static_cast<std::byte>(value); }

inline void write_u16_be(std::byte* data, std::uint16_t value) { store(data, little_host ? swap(value) : value); }
inline void write_u16_le(std::byte* data, std::uint16_t value) { store(data, little_host ? value : swap(value)); }
inline void write_u32_be(std::byte* data, std::uint32_t value) { store(data, little_host ? swap(value) : value); }
inline void write_u32_le(std::byte* data, std::uint32_t value) { store(data, little_host ? value : swap(value)); }
inline void write_u64_be(std::byte* data, std::uint64_t value) { store(data, little_host ? swap(value) : value); }
inline void write_u64_le(std::byte* data, std::uint64_t value) { store(data, little_host ? value : swap(value)); }

inline void write_i16_be(std::byte* data, std::int16_t value) { write_u16_be(data, static_cast<std::uint16_t>(value)); }
inline void write_i16_le(std::byte* data, std::int16_t value) { write_u16_le(data, static_cast<std::uint16_t>(value)); }
inline void write_i32_be(std::byte* data, std::int32_t value) { write_u32_be(data, static_cast<std::uint32_t>(value)); }
inline void write_i32_le(std::byte* data, std::int32_t value) { write_u32_le(data, static_cast<std::uint32_t>(value)); }
inline void write_i64_be(std::byte* data, std::int64_t value) { write_u64_be(data, static_cast<std::uint64_t>(value)); }
inline void write_i64_le(std::byte* data, std::int64_t value) { write_u64_le(data, static_cast<std::uint64_t>(value)); }

inline void write_u24_be(std::byte* data, std::uint32_t value) {
    for (std::size_t index = 3; index > 0; --index) { data[index - 1] = static_cast<std::byte>(value & 0xFF); value >>= 8; }
}

inline void write_u24_le(std::byte* data, std::uint32_t value) {
    for (std::size_t index = 0; index < 3; ++index) { data[index] = static_cast<std::byte>(value & 0xFF); value >>= 8; }
}

inline void write_i24_be(std::byte* data, std::int32_t value) { write_u24_be(data, static_cast<std::uint32_t>(value)); }
inline void write_i24_le(std::byte* data, std::int32_t value) { write_u24_le(data, static_cast<std::uint32_t>(value)); }

inline void write_u48_be(std::byte* data, std::uint64_t value) {
    for (std::size_t index = 6; index > 0; --index) { data[index - 1] = static_cast<std::byte>(value & 0xFF); value >>= 8; }
}

inline void write_u48_le(std::byte* data, std::uint64_t value) {
    for (std::size_t index = 0; index < 6; ++index) { data[index] = static_cast<std::byte>(value & 0xFF); value >>= 8; }
}

inline void write_i48_be(std::byte* data, std::int64_t value) { write_u48_be(data, static_cast<std::uint64_t>(value)); }
inline void write_i48_le(std::byte* data, std::int64_t value) { write_u48_le(data, static_cast<std::uint64_t>(value)); }

inline void write_f32_be(std::byte* data, float value) { write_u32_be(data, std::bit_cast<std::uint32_t>(value)); }
inline void write_f32_le(std::byte* data, float value) { write_u32_le(data, std::bit_cast<std::uint32_t>(value)); }
inline void write_f64_be(std::byte* data, double value) { write_u64_be(data, std::bit_cast<std::uint64_t>(value)); }
inline void write_f64_le(std::byte* data, double value) { write_u64_le(data, std::bit_cast<std::uint64_t>(value)); }

// text and bytes

// Fixed-length text: the fill byte pads it on the right and is not part of the value
inline std::string read_text(const std::byte* data, std::size_t size, char fill) {
    std::size_t length = size;
    while (length > 0 && static_cast<char>(data[length - 1]) == fill) { --length; }
    return std::string(reinterpret_cast<const char*>(data), length);
}

inline void write_text(std::byte* data, std::size_t size, char fill, std::string_view text) {
    const std::size_t copied = text.size() < size ? text.size() : size;
    if (copied > 0) { std::memcpy(data, text.data(), copied); }
    if (size > copied) { std::memset(data + copied, static_cast<unsigned char>(fill), size - copied); }
}

inline void read_bytes(const std::byte* data, std::byte* value, std::size_t size) {
    if (size > 0) { std::memcpy(value, data, size); }
}

inline void write_bytes(std::byte* data, const std::byte* value, std::size_t size) {
    if (size > 0) { std::memcpy(data, value, size); }
}

// The length of text before its terminating zero, looking no further than the
// maximum or the bytes available
inline std::size_t terminated_length(const std::byte* data, std::size_t available, std::size_t maximum) {
    const std::size_t limit = maximum > 0 && maximum < available ? maximum : available;
    for (std::size_t index = 0; index < limit; ++index) {
        if (data[index] == std::byte{ 0 }) { return index; }
    }
    throw DecodeError("terminated text", limit + 1, available);
}

// optional values

template <typename T>
inline std::optional<T> nullable(T raw, T sentinel) {
    if (raw == sentinel) { return std::nullopt; }
    return raw;
}

template <typename E, typename T>
inline std::optional<E> nullable_enum(T raw, T sentinel) {
    if (raw == sentinel) { return std::nullopt; }
    return static_cast<E>(raw);
}

template <typename T>
inline std::optional<Decimal> nullable_decimal(T raw, T sentinel, int exponent) {
    if (raw == sentinel) { return std::nullopt; }
    return Decimal(static_cast<std::int64_t>(raw), exponent);
}

template <typename D, typename T>
inline std::optional<D> nullable_duration(T raw, T sentinel) {
    if (raw == sentinel) { return std::nullopt; }
    return D(static_cast<std::int64_t>(raw));
}

template <typename Entries>
inline std::size_t encoded_size_of(const Entries& entries) {
    std::size_t total = 0;
    for (const auto& entry : entries) { total += entry.encoded_size(); }
    return total;
}

} // namespace iex::iexequities::deep::snap::v1_6::wire
