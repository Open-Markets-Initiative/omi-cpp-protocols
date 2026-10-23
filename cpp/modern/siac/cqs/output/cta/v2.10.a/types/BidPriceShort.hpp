#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Represents the highest price a prospective buyer is prepared to pay at a particular time for a security. Has implied 2 decimal places
struct BidPriceShort {

    static constexpr const char* name = "Bid Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr BidPriceShort()
     : value{ 0 } {}

    // constructor for BidPriceShort field
    constexpr explicit BidPriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
