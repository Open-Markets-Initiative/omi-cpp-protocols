#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {


// Contains Hex 0x00 to 0x63 (decimal 0 to 99). Represents the year, starting with year 2000.
struct ExpirationYear {

    static constexpr auto name = "Expiration Year";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExpirationYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationYear(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExpirationYear field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
