#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Represents the lowest price acceptable to a prospective seller at a particular time for a security
struct OfferPriceLong {

    static constexpr const char* name = "Offer Price Long";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OfferPriceLong()
     : value{ 0 } {}

    // constructor for OfferPriceLong field
    constexpr explicit OfferPriceLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OfferPriceLong field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OfferPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
