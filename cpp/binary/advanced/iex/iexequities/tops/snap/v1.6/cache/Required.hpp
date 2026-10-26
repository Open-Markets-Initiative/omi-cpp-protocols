#pragma once

#include <string_view>
#include <cstring>
#include <algorithm>
#include <type_traits>

namespace iex::iexequities::tops::snap::v1_6 {

/// Lightweight wrapper for required (non-optional) values.
/// Provides std::optional-compatible interface: has_value(), value(), operator bool.
/// Unlike std::optional, has_value() is constexpr true and no extra storage is used.
template<typename T>
struct required {
    using value_type = T;

    value_type value_;

    constexpr required() = default;
    constexpr required(value_type v) : value_(v) {}

    /// Converting constructor: required<string_view> → required<array<char, N>>
    /// Enabled when T has .data() and .size() (like std::array<char, N>)
    /// Zero-fills then copies — gives correct lexicographic ordering
    template<typename U = T>
    required(required<std::string_view> sv) noexcept
    requires (!std::is_same_v<U, std::string_view> && requires(U t) { t.data(); t.size(); })
    : value_{} {
        auto src = sv.value();
        auto len = std::min(src.size(), value_.size());
        std::memcpy(value_.data(), src.data(), len);
    }

    [[nodiscard]] static constexpr bool has_value() noexcept { return true; }

    [[nodiscard]] constexpr const T& value() const noexcept { return value_; }
    [[nodiscard]] constexpr T& value() noexcept { return value_; }

    constexpr explicit operator bool() const noexcept { return true; }

    // Comparison operators
    constexpr bool operator==(const required& other) const noexcept { return value_ == other.value_; }
    constexpr bool operator==(const T& other) const noexcept { return value_ == other; }
    constexpr bool operator!=(const required& other) const noexcept { return value_ != other.value_; }
    constexpr bool operator!=(const T& other) const noexcept { return value_ != other; }
    constexpr bool operator<(const required& other) const noexcept { return value_ < other.value_; }
    constexpr bool operator<(const T& other) const noexcept { return value_ < other; }
    constexpr bool operator>(const required& other) const noexcept { return value_ > other.value_; }
    constexpr bool operator>(const T& other) const noexcept { return value_ > other; }
    constexpr bool operator<=(const required& other) const noexcept { return value_ <= other.value_; }
    constexpr bool operator<=(const T& other) const noexcept { return value_ <= other; }
    constexpr bool operator>=(const required& other) const noexcept { return value_ >= other.value_; }
    constexpr bool operator>=(const T& other) const noexcept { return value_ >= other; }
};

}
