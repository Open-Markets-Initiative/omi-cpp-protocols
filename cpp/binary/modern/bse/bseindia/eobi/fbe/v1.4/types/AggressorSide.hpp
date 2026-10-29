#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Side of the incoming order.
struct AggressorSide {

    static constexpr auto name = "Aggressor Side";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AggressorSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AggressorSide(const std::uint8_t &value)
     : value{ value } {}

    // get value of AggressorSide field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
