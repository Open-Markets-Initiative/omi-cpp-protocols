#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The rate of interest that, when multiplied by the principal, par value, or face value of a bond, provides the currency amount of the periodic interest payment
struct CouponRate {

    static constexpr const char* name = "Coupon Rate";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr CouponRate()
     : value{ 0 } {}

    // constructor for CouponRate field
    constexpr explicit CouponRate(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of CouponRate field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of CouponRate field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
