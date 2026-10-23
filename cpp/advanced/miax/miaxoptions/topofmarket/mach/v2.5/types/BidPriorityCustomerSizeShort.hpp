#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// bid_priority_customer_size_short
struct bid_priority_customer_size_short {

    static constexpr const char* name = "bid_priority_customer_size_short";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr bid_priority_customer_size_short()
     : value{ 0 } {}

    constexpr bid_priority_customer_size_short(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
