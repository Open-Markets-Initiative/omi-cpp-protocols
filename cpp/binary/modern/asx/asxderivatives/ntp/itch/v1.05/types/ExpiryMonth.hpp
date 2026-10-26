#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Month of expiry for futures contract types, zero otherwise.
struct ExpiryMonth {

    static constexpr auto name = "Expiry Month";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ExpiryMonth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpiryMonth(const std::uint8_t &value)
     : value{ value } {}

    // get value of ExpiryMonth field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
