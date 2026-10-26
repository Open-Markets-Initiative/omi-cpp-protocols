#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Expiration Month (1-12)
struct ExpirationMonth {

    static constexpr auto name = "Expiration Month";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExpirationMonth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationMonth(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExpirationMonth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
