#pragma once

#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {


// Cta Block Pad Byte
struct BlockPadByte {

    static constexpr auto name = "Block Pad Byte";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr BlockPadByte()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockPadByte(const std::uint8_t &value)
     : value{ value } {}

    // get value of BlockPadByte field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
