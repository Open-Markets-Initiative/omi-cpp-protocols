#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Settlement Date as specified in the ASX 24 Contract Specifications. Reported in Unix Time (number of seconds since 00:00 1 January 1970 GMT). Convert to AEST/ADST as appropriate to determine the date.
struct ExpiryDate {

    static constexpr const char* name = "Expiry Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExpiryDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpiryDate(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExpiryDate field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
