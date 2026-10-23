#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Price of the leg
struct PriceLeg {

    static constexpr const char* name = "Price Leg";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr PriceLeg()
     : value{ 0 } {}

    // constructor for PriceLeg field
    constexpr explicit PriceLeg(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PriceLeg field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PriceLeg field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
