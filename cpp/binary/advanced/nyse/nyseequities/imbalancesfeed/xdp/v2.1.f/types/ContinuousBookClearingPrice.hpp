#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// continuous_book_clearing_price
struct continuous_book_clearing_price {

    static constexpr const char* name = "continuous_book_clearing_price";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr continuous_book_clearing_price()
     : value{ 0 } {}

    constexpr continuous_book_clearing_price(std::uint32_t v)
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
