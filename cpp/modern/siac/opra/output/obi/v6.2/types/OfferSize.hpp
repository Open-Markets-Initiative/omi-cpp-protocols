#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// The Offer Size identifies the number of contracts for sale for an option at the Offer Price.
struct OfferSize {

    static constexpr const char* name = "Offer Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OfferSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OfferSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OfferSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
