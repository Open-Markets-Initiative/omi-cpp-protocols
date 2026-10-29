#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// All transmission blocks are assigned a sequential Block Sequence Number
struct BlockSequenceNumber {

    static constexpr const char* name = "Block Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BlockSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BlockSequenceNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BlockSequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
