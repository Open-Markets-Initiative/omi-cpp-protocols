// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Coupon.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Coupon with 6 decimal places assumed. Applies to fixed income securities only.
struct Coupon {

    static constexpr const char* name = "Coupon";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Coupon()
     : value{ 0 } {}

    // constructor for Coupon field
    constexpr explicit Coupon(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Coupon field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Coupon field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
