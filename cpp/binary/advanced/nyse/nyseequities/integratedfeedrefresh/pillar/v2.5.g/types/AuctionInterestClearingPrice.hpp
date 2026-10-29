#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// auction_interest_clearing_price
struct auction_interest_clearing_price {

    static constexpr const char* name = "auction_interest_clearing_price";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr auction_interest_clearing_price()
     : value{ 0 } {}

    constexpr auction_interest_clearing_price(std::int32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int32_t value;
};
}
