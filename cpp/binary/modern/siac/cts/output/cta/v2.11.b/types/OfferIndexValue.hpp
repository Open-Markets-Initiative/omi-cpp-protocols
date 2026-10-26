#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the value of the index calculation formula using the current offer values of the component securities. Has implied 6 decimal places
struct OfferIndexValue {

    static constexpr const char* name = "Offer Index Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr OfferIndexValue()
     : value{ 0 } {}

    // constructor for OfferIndexValue field
    constexpr explicit OfferIndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OfferIndexValue field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OfferIndexValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
