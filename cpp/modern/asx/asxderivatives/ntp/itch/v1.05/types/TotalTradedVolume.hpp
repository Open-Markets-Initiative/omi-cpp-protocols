#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Total Traded Volume.
struct TotalTradedVolume {

    static constexpr const char* name = "Total Traded Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TotalTradedVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalTradedVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TotalTradedVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
