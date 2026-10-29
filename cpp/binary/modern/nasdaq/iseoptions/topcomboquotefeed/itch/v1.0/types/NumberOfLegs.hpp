#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {


// Number of legs in the strategy NOTE: Leg field offsets below are an equation, where “n” is the zero based leg number (0, 1, …)
struct NumberOfLegs {

    static constexpr auto name = "Number Of Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfLegs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfLegs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
