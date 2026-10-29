#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

// Instrument quantity being added to the complex book (may be less than the number entered).
struct QuantityShort {

    static constexpr const char* name = "Quantity Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr QuantityShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuantityShort(const std::uint16_t value)
     : value{ value } {}

    // get value of QuantityShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
