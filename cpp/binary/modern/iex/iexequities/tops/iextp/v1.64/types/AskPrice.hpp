#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_64 {

// Best quoted ask price
struct AskPrice {

    static constexpr const char* name = "Ask Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr AskPrice()
     : value{ 0 } {}

    // constructor for AskPrice field
    constexpr explicit AskPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AskPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AskPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
