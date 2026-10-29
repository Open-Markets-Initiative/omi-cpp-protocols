#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {


// Num Body
struct NumBody {

    static constexpr auto name = "Num Body";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumBody()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumBody(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumBody field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
