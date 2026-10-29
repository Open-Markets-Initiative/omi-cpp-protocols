#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Reserved for future expansion, Value is 0
struct Sequence0 {

    static constexpr auto name = "Sequence 0";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type static_value = 0;

    // default constructor
    constexpr Sequence0()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Sequence0(const std::uint8_t &value)
     : value{ value } {}

    // get value of Sequence0 field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
