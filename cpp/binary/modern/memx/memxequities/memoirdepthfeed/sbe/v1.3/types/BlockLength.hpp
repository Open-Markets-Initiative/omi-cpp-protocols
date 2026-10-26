#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Memx Udp Message Type
struct BlockLength {

    static constexpr const char* name = "Block Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BlockLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockLength(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BlockLength field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
