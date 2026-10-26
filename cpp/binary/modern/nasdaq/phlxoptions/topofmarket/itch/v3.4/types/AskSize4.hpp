#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Aggregated number of contracts on the ask side being displayed in the options market at the current time.
struct AskSize4 {

    static constexpr const char* name = "Ask Size 4";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSize4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSize4(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskSize4 field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
