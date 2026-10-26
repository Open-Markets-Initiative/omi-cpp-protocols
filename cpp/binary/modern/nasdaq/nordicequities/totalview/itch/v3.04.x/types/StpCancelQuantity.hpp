#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Quantity deleted due to self trade prevention
struct StpCancelQuantity {

    static constexpr const char* name = "Stp Cancel Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr StpCancelQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StpCancelQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StpCancelQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
