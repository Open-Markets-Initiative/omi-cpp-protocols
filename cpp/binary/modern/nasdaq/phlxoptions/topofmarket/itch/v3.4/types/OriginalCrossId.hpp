#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Indicates the internal control number (cross id) associated with the given trade transaction in the options market system.
struct OriginalCrossId {

    static constexpr const char* name = "Original Cross Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalCrossId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalCrossId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalCrossId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
