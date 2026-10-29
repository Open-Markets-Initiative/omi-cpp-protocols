#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// Instrument quantity added to the complex book (may be less than the number entered).
struct Quantity {

    static constexpr const char* name = "Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Quantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Quantity(const std::uint32_t value)
     : value{ value } {}

    // get value of Quantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
