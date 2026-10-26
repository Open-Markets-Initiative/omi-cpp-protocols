#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Reported Premium Price of an option contract in the original trade report message on this feed.
struct OriginalPrice {

    static constexpr const char* name = "Original Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr OriginalPrice()
     : value{ 0 } {}

    // constructor for OriginalPrice field
    constexpr explicit OriginalPrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalPrice field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
