#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Nasdaq internal tracking number
struct TrackingNumber {

    static constexpr const char* name = "Tracking Number";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TrackingNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrackingNumber(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of TrackingNumber field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
