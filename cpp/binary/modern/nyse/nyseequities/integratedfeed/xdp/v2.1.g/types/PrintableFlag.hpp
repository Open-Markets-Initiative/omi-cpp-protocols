#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {


// Printable flag values
struct PrintableFlag {

    static constexpr auto name = "Printable Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PrintableFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrintableFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of PrintableFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
