#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Bid Price of the prevailing Composite Market.
struct CompositeMarketBidPrice {

    static constexpr const char* name = "Composite Market Bid Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr CompositeMarketBidPrice()
     : value{ 0 } {}

    // constructor for CompositeMarketBidPrice field
    constexpr explicit CompositeMarketBidPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of CompositeMarketBidPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of CompositeMarketBidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
