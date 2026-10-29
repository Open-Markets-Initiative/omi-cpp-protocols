#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Price In A Valid Currency
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // constructor for Price field
    constexpr explicit Price(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of Price field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of Price field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
