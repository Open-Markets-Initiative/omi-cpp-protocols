#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the stated price per share for which the underlying security may be purchased (in the case of a call) or sold (in the case of a put) by the option holder upon exercise of the option contract.
struct StrikePriceShort {

    static constexpr const char* name = "Strike Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint16_t;

    // default constructor
    constexpr StrikePriceShort()
     : value{ 0 } {}

    // constructor for StrikePriceShort field
    constexpr explicit StrikePriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of StrikePriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of StrikePriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
