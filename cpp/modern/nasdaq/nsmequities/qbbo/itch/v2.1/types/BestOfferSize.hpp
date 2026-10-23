#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Denotes the aggregated number of shares available for display within the execution system at the best offer price.
struct BestOfferSize {

    static constexpr const char* name = "Best Offer Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BestOfferSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestOfferSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestOfferSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
