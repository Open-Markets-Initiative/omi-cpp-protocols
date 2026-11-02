#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {


// The sub fraction
struct SubFraction {

    static constexpr auto name = "Sub Fraction";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SubFraction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SubFraction(const std::uint8_t &value)
     : value{ value } {}

    // get value of SubFraction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
