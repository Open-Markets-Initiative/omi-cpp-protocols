#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Last Trading Day as specified in the ASX 24 Contract Specifications. Reported in Unix Time (number of seconds since 00:00 1 January 1970 GMT). Convert to AEST/ADST as appropriate to determine the date.
struct LastTradingDate {

    static constexpr const char* name = "Last Trading Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastTradingDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastTradingDate(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LastTradingDate field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
