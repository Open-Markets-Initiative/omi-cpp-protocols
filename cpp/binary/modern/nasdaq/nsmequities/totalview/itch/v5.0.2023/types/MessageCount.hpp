#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Number of messages to follow this header
struct MessageCount {

    static constexpr const char* name = "Message Count";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageCount(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of MessageCount field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
