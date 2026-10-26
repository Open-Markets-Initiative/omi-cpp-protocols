#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Consolidated last price. Has implied 6 decimal places
struct ConsolidatedLastPrice {

    static constexpr const char* name = "Consolidated Last Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ConsolidatedLastPrice()
     : value{ 0 } {}

    // constructor for ConsolidatedLastPrice field
    constexpr explicit ConsolidatedLastPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ConsolidatedLastPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ConsolidatedLastPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
