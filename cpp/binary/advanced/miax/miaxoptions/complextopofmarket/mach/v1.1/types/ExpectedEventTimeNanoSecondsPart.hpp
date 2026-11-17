// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/ExpectedEventTimeNanoSecondsPart.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// expected_event_time_nano_seconds_part
struct expected_event_time_nano_seconds_part {

    static constexpr const char* name = "expected_event_time_nano_seconds_part";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr expected_event_time_nano_seconds_part()
     : value{ 0 } {}

    constexpr expected_event_time_nano_seconds_part(std::uint32_t v)
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

  protected:
    std::uint32_t value;
};
}
