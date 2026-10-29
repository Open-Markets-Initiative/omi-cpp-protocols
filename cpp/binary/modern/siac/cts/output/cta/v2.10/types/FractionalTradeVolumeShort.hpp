#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// The Fractional Trade Volume contains the total number of shares which traded in a single transaction for an individual security.
struct FractionalTradeVolumeShort {

    static constexpr const char* name = "Fractional Trade Volume Short";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint32_t;

    // default constructor
    constexpr FractionalTradeVolumeShort()
     : value{ 0 } {}

    // constructor for FractionalTradeVolumeShort field
    constexpr explicit FractionalTradeVolumeShort(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of FractionalTradeVolumeShort field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of FractionalTradeVolumeShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
