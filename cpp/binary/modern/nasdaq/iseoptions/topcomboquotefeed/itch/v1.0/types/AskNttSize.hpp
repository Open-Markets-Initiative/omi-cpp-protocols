#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Limit Ask size that can’t be traded through.
struct AskNttSize {

    static constexpr const char* name = "Ask Ntt Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskNttSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskNttSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskNttSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
