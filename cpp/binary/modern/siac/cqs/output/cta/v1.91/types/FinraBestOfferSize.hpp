#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Contains the FINRA ADF provided FINRA Best Offer Size associated with the FINRA Best Offer Price that had the FINRA Best Offer
struct FinraBestOfferSize {

    static constexpr const char* name = "Finra Best Offer Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr FinraBestOfferSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBestOfferSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of FinraBestOfferSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
