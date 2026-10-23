#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the total dollar worth of the daily trade transactions. Has implied 6 decimal places
struct DollarValue {

    static constexpr const char* name = "Dollar Value";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr DollarValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DollarValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of DollarValue field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
