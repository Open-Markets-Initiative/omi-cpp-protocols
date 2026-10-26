#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Odd lot size
struct OddLotSize {

    static constexpr const char* name = "Odd Lot Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OddLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OddLotSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OddLotSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
