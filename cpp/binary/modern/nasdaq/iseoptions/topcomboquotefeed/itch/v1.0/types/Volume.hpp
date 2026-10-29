#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Total traded quantity.
struct Volume {

    static constexpr const char* name = "Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Volume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Volume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
