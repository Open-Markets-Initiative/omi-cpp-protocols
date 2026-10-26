#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Monetary value equivalent to the minimum price fluctuation
struct MinPriceIncrementAmount {

    static constexpr const char* name = "Min Price Increment Amount";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MinPriceIncrementAmount()
     : value{ 0 } {}

    // constructor for MinPriceIncrementAmount field
    constexpr explicit MinPriceIncrementAmount(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementAmount field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrementAmount field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
