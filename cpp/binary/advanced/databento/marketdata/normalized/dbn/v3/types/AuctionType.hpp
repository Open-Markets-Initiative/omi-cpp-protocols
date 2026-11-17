// Databento.MarketData.Normalized.Dbn.v3: types/AuctionType.hpp
#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// auction_type
struct auction_type {

    static constexpr const char* name = "auction_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr auction_type()
     : value{ 0 } {}

    constexpr auction_type(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
