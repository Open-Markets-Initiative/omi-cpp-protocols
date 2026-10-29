#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Represents the Best Offer Size associated with the Best Bid Price on a consolidated basis
struct BestOfferSizeLong {

    static constexpr const char* name = "Best Offer Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BestOfferSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestOfferSizeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestOfferSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
