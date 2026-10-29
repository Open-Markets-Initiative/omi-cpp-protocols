#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Represents the date the security last traded
struct PreviousClosePriceDate {

    static constexpr const char* name = "Previous Close Price Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PreviousClosePriceDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PreviousClosePriceDate(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PreviousClosePriceDate field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
