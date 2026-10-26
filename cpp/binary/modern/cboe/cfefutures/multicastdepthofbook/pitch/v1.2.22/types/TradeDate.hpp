#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Current Trade Date
struct TradeDate {

    static constexpr const char* name = "Trade Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeDate(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeDate field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
