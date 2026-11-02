#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// Sometimes multiple errors are sent together; 1 when this is the last in the series
struct IsLast {

    static constexpr auto name = "Is Last";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr IsLast()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsLast(const std::uint8_t &value)
     : value{ value } {}

    // get value of IsLast field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
