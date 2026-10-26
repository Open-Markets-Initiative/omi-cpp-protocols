#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Lot Type
struct LotType {

    static constexpr auto name = "Lot Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LotType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LotType(const std::uint8_t &value)
     : value{ value } {}

    // get value of LotType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
