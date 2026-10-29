#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// Day of the Month of expiration (1-31)
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
