#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, the price at which all eligible auction-only interest would trade, subject to auction collars For NYSE, the price closest to the reference price where the imbalance of closing-only interest is 0. If a closing-only clearing price is not reached, it is defaulted to 0.
struct ClosingOnlyClearingPrice {

    static constexpr const char* name = "Closing Only Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ClosingOnlyClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClosingOnlyClearingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of ClosingOnlyClearingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
