// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Price.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Price with 6 decimal places assumed.
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // constructor for Price field
    constexpr explicit Price(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Price field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Price field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
