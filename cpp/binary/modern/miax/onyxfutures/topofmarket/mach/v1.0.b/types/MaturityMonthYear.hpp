#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Maturity Month-Year is the expiration date of a Simple Instrument
struct MaturityMonthYear {

    static constexpr const char* name = "Maturity Month Year";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MaturityMonthYear()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityMonthYear(const std::uint32_t value)
     : value{ value } {}

    // get value of MaturityMonthYear field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
