#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Time unit multiplier for the frequency of the bond's coupon payment
struct CouponFrequencyPeriod {

    static constexpr const char* name = "Coupon Frequency Period";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 65535;

    // default constructor
    constexpr CouponFrequencyPeriod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CouponFrequencyPeriod(const std::uint16_t value)
     : value{ value } {}

    // get value of CouponFrequencyPeriod field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
