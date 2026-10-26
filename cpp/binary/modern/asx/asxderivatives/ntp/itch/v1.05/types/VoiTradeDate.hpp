#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Trade Date the VOI information is applicable to.
struct VoiTradeDate {

    static constexpr const char* name = "Voi Trade Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr VoiTradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit VoiTradeDate(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of VoiTradeDate field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
