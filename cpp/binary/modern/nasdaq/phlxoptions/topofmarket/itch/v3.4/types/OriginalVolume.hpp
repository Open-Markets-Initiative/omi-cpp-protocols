#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Reported number of contracts in the original trade report message on this feed.
struct OriginalVolume {

    static constexpr const char* name = "Original Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
