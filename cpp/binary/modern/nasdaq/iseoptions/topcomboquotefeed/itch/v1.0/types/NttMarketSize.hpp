#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// The aggregated NTT Market Size.
struct NttMarketSize {

    static constexpr const char* name = "Ntt Market Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NttMarketSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NttMarketSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NttMarketSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
