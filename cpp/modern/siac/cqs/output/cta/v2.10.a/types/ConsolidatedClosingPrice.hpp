#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Consolidated Closing Price. Has implied 6 decimal places
struct ConsolidatedClosingPrice {

    static constexpr const char* name = "Consolidated Closing Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedClosingPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedClosingPrice field
    constexpr explicit ConsolidatedClosingPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedClosingPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedClosingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
