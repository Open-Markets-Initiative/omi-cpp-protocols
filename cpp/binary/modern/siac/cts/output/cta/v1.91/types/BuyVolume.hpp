#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// The Buy Volume represents the reported imbalance of buy orders without matching sell orders for the security for a Participant.
struct BuyVolume {

    static constexpr const char* name = "Buy Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BuyVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BuyVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BuyVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
