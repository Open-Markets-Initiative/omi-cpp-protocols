#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
struct OfferSizeLong {

    static constexpr const char* name = "Offer Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OfferSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferSizeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OfferSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
