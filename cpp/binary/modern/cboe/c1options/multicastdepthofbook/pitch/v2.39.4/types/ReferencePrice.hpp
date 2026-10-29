#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// BBO Collared auction price
struct ReferencePrice {

    static constexpr const char* name = "Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr ReferencePrice()
     : value{ 0 } {}

    // constructor for ReferencePrice field
    constexpr explicit ReferencePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of ReferencePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of ReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
