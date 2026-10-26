#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The total number of contracts of the new order being added to the book.
struct VolumeShort {

    static constexpr const char* name = "Volume Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr VolumeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit VolumeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of VolumeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
