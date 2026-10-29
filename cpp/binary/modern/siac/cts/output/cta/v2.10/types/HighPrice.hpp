#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// The High Price represents the highest price paid for a security during the trading day
struct HighPrice {

    static constexpr const char* name = "High Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr HighPrice()
     : value{ 0 } {}

    // constructor for HighPrice field
    constexpr explicit HighPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of HighPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of HighPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
