#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Nominal value
struct NominalValue {

    static constexpr const char* name = "Nominal Value";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NominalValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NominalValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NominalValue field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
