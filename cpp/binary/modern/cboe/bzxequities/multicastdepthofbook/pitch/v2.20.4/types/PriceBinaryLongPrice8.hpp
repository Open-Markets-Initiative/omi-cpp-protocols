#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// The limit order price
struct PriceBinaryLongPrice8 {

    static constexpr const char* name = "Price Binary Long Price 8";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr PriceBinaryLongPrice8()
     : value{ 0 } {}

    // constructor for PriceBinaryLongPrice8 field
    constexpr explicit PriceBinaryLongPrice8(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of PriceBinaryLongPrice8 field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of PriceBinaryLongPrice8 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
