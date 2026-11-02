#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The price display format
struct PriceDisplayFormat {

    static constexpr auto name = "Price Display Format";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceDisplayFormat()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceDisplayFormat(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceDisplayFormat field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
