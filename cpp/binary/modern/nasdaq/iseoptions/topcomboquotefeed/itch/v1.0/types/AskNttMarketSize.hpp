#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The aggregated NTT Market Size on Ask Size.
struct AskNttMarketSize {

    static constexpr const char* name = "Ask Ntt Market Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskNttMarketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskNttMarketSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskNttMarketSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
