#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// auction_book_clearing_price
struct auction_book_clearing_price {

    static constexpr const char* name = "auction_book_clearing_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr auction_book_clearing_price()
     : value{ 0 } {}

    constexpr auction_book_clearing_price(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
