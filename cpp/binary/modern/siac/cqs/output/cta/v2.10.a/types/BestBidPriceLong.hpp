#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the Best Bid Price on a consolidated basis
struct BestBidPriceLong {

    static constexpr const char* name = "Best Bid Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr BestBidPriceLong()
     : value{ 0 } {}

    // constructor for BestBidPriceLong field
    constexpr explicit BestBidPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BestBidPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BestBidPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
