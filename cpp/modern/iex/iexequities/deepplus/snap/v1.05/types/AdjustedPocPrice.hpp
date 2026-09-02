#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Corporate action adjusted previous official closing price
struct AdjustedPocPrice {

    static constexpr const char* name = "Adjusted Poc Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr AdjustedPocPrice()
     : value{ 0 } {}

    // constructor for AdjustedPocPrice field
    constexpr explicit AdjustedPocPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AdjustedPocPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AdjustedPocPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
