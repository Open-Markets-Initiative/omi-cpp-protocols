#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Number of decimals in Nominal Value
struct DecimalsInNominalValue {

    static constexpr const char* name = "Decimals In Nominal Value";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr DecimalsInNominalValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecimalsInNominalValue(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of DecimalsInNominalValue field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
