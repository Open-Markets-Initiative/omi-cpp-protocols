#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"
#include "../common/Day.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// time_reference
struct time_reference {

    static constexpr const char* name = "time_reference";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr time_reference()
     : value{ 0 } {}

    constexpr time_reference(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

    // time_reference on a day: its seconds since midnight, America/Chicago, as UTC Unix nanoseconds;
    // none where it has no value
    [[nodiscard]] std::optional<std::int64_t> utc(const calendar::Day& day) const {
        const auto held = get();
        if (!held.has_value()) {
            return std::nullopt;
        }
        return calendar::midnight(day, "America/Chicago").utc(static_cast<std::int64_t>(held.value()) * 1000000000);
    }

  protected:
    std::uint32_t value;
};
}
