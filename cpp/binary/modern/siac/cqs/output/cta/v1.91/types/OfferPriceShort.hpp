#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Represents the lowest price acceptable to a prospective seller at a particular time for a security
struct OfferPriceShort {

    static constexpr const char* name = "Offer Price Short";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint16_t;

    // default constructor
    constexpr OfferPriceShort()
     : value{ 0 } {}

    // constructor for OfferPriceShort field
    constexpr explicit OfferPriceShort(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OfferPriceShort field
    [[nodiscard]] std::uint16_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OfferPriceShort field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint16_t value;
};
}
