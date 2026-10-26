#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Original total number of shares which traded in a single transaction. Has implied 6 decimal places
struct OriginalFractionalTradeVolume {

    static constexpr const char* name = "Original Fractional Trade Volume";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalFractionalTradeVolume()
     : value{ 0 } {}

    // constructor for OriginalFractionalTradeVolume field
    constexpr explicit OriginalFractionalTradeVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalFractionalTradeVolume field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalFractionalTradeVolume field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
