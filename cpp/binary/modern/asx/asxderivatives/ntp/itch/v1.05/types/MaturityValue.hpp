#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// The number of days or years to maturity for bills or bonds as specified in the ASX 24 Contract Specifications.
struct MaturityValue {

    static constexpr auto name = "Maturity Value";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MaturityValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityValue(const std::uint8_t &value)
     : value{ value } {}

    // get value of MaturityValue field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
