#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Bid Price represents the highest price a prospective buyer is prepared to pay; Lower Limit Price Band represents the lower price band value when Security Status Indicator is Limit Up-Limit Down Price Band
struct BidPriceLowerLimitPriceBand {

    static constexpr const char* name = "Bid Price Lower Limit Price Band";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr BidPriceLowerLimitPriceBand()
     : value{ 0 } {}

    // constructor for BidPriceLowerLimitPriceBand field
    constexpr explicit BidPriceLowerLimitPriceBand(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPriceLowerLimitPriceBand field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPriceLowerLimitPriceBand field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
