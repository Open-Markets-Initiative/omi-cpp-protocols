// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: types/ExpirationYear.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


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
