#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// The Offer Size identifies the number of round-lots, for a security
struct OfferSizeShort {

    static constexpr const char* name = "Offer Size Short";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr OfferSizeShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferSizeShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of OfferSizeShort field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
