#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the length of the Message Data field
struct MessageDataLength {

    static constexpr const char* name = "Message Data Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageDataLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageDataLength(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of MessageDataLength field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
