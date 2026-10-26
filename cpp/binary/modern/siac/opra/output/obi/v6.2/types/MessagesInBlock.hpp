#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {


// The number of messages contained in the block data of the transmission block.
struct MessagesInBlock {

    static constexpr auto name = "Messages In Block";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MessagesInBlock()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessagesInBlock(const std::uint8_t &value)
     : value{ value } {}

    // get value of MessagesInBlock field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
