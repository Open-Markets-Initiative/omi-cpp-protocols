#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Price At Which Orders Will Trade At The Open
struct CalculatedOpeningPrice {

    static constexpr const char* name = "Calculated Opening Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr CalculatedOpeningPrice()
     : value{ 0 } {}

    // constructor for CalculatedOpeningPrice field
    constexpr explicit CalculatedOpeningPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of CalculatedOpeningPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of CalculatedOpeningPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
