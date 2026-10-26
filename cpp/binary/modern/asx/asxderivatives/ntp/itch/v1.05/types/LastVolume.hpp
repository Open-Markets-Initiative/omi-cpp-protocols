#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Last Traded Volume.
struct LastVolume {

    static constexpr const char* name = "Last Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LastVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
