#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Leg Ratio
struct LegRatio {

    static constexpr const char* name = "Leg Ratio";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LegRatio()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatio(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LegRatio field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
