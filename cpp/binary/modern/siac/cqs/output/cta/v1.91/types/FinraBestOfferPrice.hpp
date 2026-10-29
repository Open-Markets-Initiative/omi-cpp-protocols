#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Contains the FINRAADF provided Best FINRA Offer Price that is the FINRA Best Offer
struct FinraBestOfferPrice {

    static constexpr const char* name = "Finra Best Offer Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr FinraBestOfferPrice()
     : value{ 0 } {}

    // constructor for FinraBestOfferPrice field
    constexpr explicit FinraBestOfferPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of FinraBestOfferPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of FinraBestOfferPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
