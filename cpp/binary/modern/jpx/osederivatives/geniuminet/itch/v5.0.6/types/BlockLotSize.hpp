#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Block lot size
struct BlockLotSize {

    static constexpr const char* name = "Block Lot Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BlockLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockLotSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BlockLotSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
