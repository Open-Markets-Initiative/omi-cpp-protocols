#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {


// Specifies placement of the decimal point in price fields for this security.
struct PriceScaleCode {

    static constexpr auto name = "Price Scale Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceScaleCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceScaleCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceScaleCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
