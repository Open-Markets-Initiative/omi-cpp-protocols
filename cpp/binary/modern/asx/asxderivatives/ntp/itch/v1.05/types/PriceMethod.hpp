#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Pricing method
struct PriceMethod {

    static constexpr auto name = "Price Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
