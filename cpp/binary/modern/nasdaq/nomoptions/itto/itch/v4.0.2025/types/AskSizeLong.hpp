#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The ask contracts of the new quote.
struct AskSizeLong {

    static constexpr const char* name = "Ask Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSizeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
