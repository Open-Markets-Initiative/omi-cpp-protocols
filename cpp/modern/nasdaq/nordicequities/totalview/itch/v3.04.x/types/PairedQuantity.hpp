#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Shares eligible to match at the reference price
struct PairedQuantity {

    static constexpr const char* name = "Paired Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr PairedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of PairedQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
