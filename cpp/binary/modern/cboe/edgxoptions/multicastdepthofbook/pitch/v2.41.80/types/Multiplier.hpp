#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Width multiplier.
struct Multiplier {

    static constexpr const char* name = "Multiplier";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr Multiplier()
     : value{ 0 } {}

    // constructor for Multiplier field
    constexpr explicit Multiplier(const std::uint32_t value)
     : value{ value } {}

    // get underlying integer of Multiplier field
    [[nodiscard]] std::uint32_t integer() const {
        return value;
    }

    // decimal value of Multiplier field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
