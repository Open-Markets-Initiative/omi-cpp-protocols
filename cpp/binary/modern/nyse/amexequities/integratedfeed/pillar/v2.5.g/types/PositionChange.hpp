#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {


// Currently defaulted to 0.
struct PositionChange {

    static constexpr auto name = "Position Change";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PositionChange()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PositionChange(const std::uint8_t &value)
     : value{ value } {}

    // get value of PositionChange field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
