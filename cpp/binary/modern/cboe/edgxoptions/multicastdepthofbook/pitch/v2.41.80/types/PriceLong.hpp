#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// The limit order price.
struct PriceLong {

    static constexpr const char* name = "Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr PriceLong()
     : value{ 0 } {}

    // constructor for PriceLong field
    constexpr explicit PriceLong(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of PriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of PriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
