#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../common/Day.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// second
struct second {

    static constexpr const char* name = "second";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr second()
     : value{ 0 } {}

    second(std::uint32_t v)
     : value{ static_cast<std::uint32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint32_t>(__builtin_bswap32(value))};
    }

    void set(std::uint32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

    // second on a day: its seconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where it has no value
    [[nodiscard]] std::optional<std::int64_t> utc(const calendar::Day& day) const {
        const auto held = get();
        if (!held.has_value()) {
            return std::nullopt;
        }
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(held.value()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
