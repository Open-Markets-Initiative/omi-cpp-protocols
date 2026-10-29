#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_9 {

// The Low Price represents the lowest price paid for a security during the trading day
struct LowPrice {

    static constexpr const char* name = "Low Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr LowPrice()
     : value{ 0 } {}

    // constructor for LowPrice field
    constexpr explicit LowPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LowPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LowPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
