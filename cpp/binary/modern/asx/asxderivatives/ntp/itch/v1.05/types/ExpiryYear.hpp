#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Year of expiry (YYYY) for futures contract types, zero otherwise.
struct ExpiryYear {

    static constexpr const char* name = "Expiry Year";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ExpiryYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpiryYear(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExpiryYear field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
