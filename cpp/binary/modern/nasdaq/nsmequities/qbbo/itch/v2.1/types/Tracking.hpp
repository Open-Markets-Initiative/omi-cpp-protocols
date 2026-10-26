#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Nasdaq internal tracking number
struct Tracking {

    static constexpr const char* name = "Tracking";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Tracking()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Tracking(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of Tracking field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
