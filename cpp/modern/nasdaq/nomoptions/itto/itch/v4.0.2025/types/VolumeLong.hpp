#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The total number of contracts of the new order being added to the book.
struct VolumeLong {

    static constexpr const char* name = "Volume Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr VolumeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit VolumeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of VolumeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
