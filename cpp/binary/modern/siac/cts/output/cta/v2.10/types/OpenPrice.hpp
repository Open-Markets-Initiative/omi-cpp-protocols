#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// The Open Price represents the first qualifying price paid for a security during the trading day.
struct OpenPrice {

    static constexpr const char* name = "Open Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OpenPrice()
     : value{ 0 } {}

    // constructor for OpenPrice field
    constexpr explicit OpenPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OpenPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OpenPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
