#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The ask contracts of the new quote.
struct AskSizeShort {

    static constexpr const char* name = "Ask Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr AskSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSizeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
