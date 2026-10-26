#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../common/Day.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// timestamp
struct timestamp {

    static constexpr const char* name = "timestamp";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr timestamp()
     : value{ 0 } {}

    timestamp(std::uint64_t v)
     : value{ static_cast<std::uint64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint64_t>(__builtin_bswap64(value))};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

    // timestamp on a day: its nanoseconds since midnight, UTC, as UTC Unix nanoseconds;
    // none where it has no value
    [[nodiscard]] std::optional<std::int64_t> utc(const calendar::Day& day) const {
        const auto held = get();
        if (!held.has_value()) {
            return std::nullopt;
        }
        return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(held.value()));
    }

  protected:
    std::uint64_t value;
};
}
