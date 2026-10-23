#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {


// Last two digits of the year of the option expiration
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
