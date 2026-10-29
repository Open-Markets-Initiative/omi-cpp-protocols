#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The limit order price
struct LongPrice {

    static constexpr const char* name = "Long Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr LongPrice()
     : value{ 0 } {}

    // constructor for LongPrice field
    constexpr explicit LongPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of LongPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of LongPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
