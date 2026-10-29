#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Aggregated number of contracts on the ask side being displayed in the options market at the current time.
struct AskSize {

    static constexpr const char* name = "Ask Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
