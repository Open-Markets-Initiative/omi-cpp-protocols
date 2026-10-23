#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// The day count convention used in interest calculations for a bond or an interest bearing security
struct CouponDayCount {

    static constexpr auto name = "Coupon Day Count";
    static constexpr std::size_t size = 20;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CouponDayCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CouponDayCount(const type &value)
     : value{ value } {}

    // get value of CouponDayCount field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
