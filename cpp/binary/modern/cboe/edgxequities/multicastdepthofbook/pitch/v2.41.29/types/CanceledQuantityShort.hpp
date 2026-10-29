#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

// Instrument quantity canceled
struct CanceledQuantityShort {

    static constexpr const char* name = "Canceled Quantity Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CanceledQuantityShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledQuantityShort(const std::uint16_t value)
     : value{ value } {}

    // get value of CanceledQuantityShort field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
