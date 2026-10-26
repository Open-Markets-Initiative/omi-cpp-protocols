#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The coupon percentage rate for bonds.
struct CouponRate {

    static constexpr const char* name = "Coupon Rate";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CouponRate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CouponRate(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of CouponRate field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
