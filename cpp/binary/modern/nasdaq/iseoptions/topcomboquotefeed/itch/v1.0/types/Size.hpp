#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Aggregated number of contracts on the bid or ask side being displayed in the options market at the current time.
struct Size {

    static constexpr const char* name = "Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Size()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Size(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Size field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
