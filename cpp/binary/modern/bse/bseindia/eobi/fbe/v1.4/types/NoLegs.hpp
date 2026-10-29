#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Number of Legs repeating group instances.
struct NoLegs {

    static constexpr auto name = "No Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NoLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoLegs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoLegs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
