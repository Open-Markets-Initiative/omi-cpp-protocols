#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Lower 2 bytes of the 4 byte sum of all the bytes in the block, excluding this Block Checksum field
struct BlockChecksum {

    static constexpr const char* name = "Block Checksum";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BlockChecksum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockChecksum(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BlockChecksum field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
