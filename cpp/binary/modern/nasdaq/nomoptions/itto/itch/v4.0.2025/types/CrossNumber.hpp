#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Trade Group Id. Ties together all trades of a given atomic transaction in the matching engine.
struct CrossNumber {

    static constexpr const char* name = "Cross Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CrossNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CrossNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
