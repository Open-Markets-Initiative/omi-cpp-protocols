#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Option ID assigned daily, valid for trading day.
struct OptionId {

    static constexpr const char* name = "Option Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OptionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OptionId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OptionId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
