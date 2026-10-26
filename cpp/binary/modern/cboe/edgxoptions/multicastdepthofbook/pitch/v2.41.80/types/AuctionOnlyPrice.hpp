#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Uncollared VMIM price computed on the queuing book only.
struct AuctionOnlyPrice {

    static constexpr const char* name = "Auction Only Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr AuctionOnlyPrice()
     : value{ 0 } {}

    // constructor for AuctionOnlyPrice field
    constexpr explicit AuctionOnlyPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of AuctionOnlyPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of AuctionOnlyPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
