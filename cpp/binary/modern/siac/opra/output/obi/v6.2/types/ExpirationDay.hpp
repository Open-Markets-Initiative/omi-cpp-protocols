#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {


// Contains Hex 0x01 to 0x1F (decimal 1 to 31), indicating the day of the month the series expires.
struct ExpirationDay {

    static constexpr auto name = "Expiration Day";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExpirationDay()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationDay(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExpirationDay field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
