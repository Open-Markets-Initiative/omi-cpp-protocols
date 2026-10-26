#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// SOQ upper strike price.
struct UpperStrikePrice {

    static constexpr const char* name = "Upper Strike Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr UpperStrikePrice()
     : value{ 0 } {}

    // constructor for UpperStrikePrice field
    constexpr explicit UpperStrikePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of UpperStrikePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of UpperStrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
