#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Represents the reported imbalance of sell orders without matching buy orders for the security for a Participant
struct SellVolume {

    static constexpr const char* name = "Sell Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SellVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SellVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
