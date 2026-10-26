#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the highest price a prospective buyer is prepared to pay at a particular time for a security. Has implied 6 decimal places
struct BidPriceLong {

    static constexpr const char* name = "Bid Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr BidPriceLong()
     : value{ 0 } {}

    // constructor for BidPriceLong field
    constexpr explicit BidPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
