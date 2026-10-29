#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Price at which the auction book and the continuous book would match.
struct IndicativePrice {

    static constexpr const char* name = "Indicative Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr IndicativePrice()
     : value{ 0 } {}

    // constructor for IndicativePrice field
    constexpr explicit IndicativePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of IndicativePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of IndicativePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
