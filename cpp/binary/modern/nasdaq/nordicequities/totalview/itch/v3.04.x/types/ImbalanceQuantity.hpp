#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Shares not paired at the reference price
struct ImbalanceQuantity {

    static constexpr const char* name = "Imbalance Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ImbalanceQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ImbalanceQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
