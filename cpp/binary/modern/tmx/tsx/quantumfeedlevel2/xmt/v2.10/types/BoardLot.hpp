#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Contains The Board Lot Size
struct BoardLot {

    static constexpr const char* name = "Board Lot";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr BoardLot()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BoardLot(const std::uint16_t value)
     : value{ value } {}

    // get value of BoardLot field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
