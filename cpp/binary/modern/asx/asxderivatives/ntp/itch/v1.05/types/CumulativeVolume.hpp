#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Volume traded for the specified VOI Trade Date.
struct CumulativeVolume {

    static constexpr const char* name = "Cumulative Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CumulativeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CumulativeVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CumulativeVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
