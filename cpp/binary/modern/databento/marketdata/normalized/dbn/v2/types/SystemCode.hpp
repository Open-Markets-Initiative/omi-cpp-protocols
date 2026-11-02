#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {


// Type of system message
struct SystemCode {

    static constexpr auto name = "System Code";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SystemCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SystemCode(const std::uint8_t &value)
     : value{ value } {}

    // get value of SystemCode field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
