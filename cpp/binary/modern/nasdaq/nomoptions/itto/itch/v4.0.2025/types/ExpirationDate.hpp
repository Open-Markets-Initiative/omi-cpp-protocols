#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Day of the Month of expiration (1-31)
struct ExpirationDate {

    static constexpr auto name = "Expiration Date";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExpirationDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationDate(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExpirationDate field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
