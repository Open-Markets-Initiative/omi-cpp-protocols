#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Type of the trade.
struct TradeType {

    static constexpr auto name = "Trade Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradeType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeType(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradeType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
