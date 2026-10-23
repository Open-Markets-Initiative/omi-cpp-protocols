#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Size in bytes of entire transmission block
struct BlockSize {

    static constexpr const char* name = "Block Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BlockSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockSize(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BlockSize field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
