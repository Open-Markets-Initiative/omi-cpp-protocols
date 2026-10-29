#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// The Previous Close Price represents the last qualifying price paid for a security during the trading day
struct PreviousClosePrice {

    static constexpr const char* name = "Previous Close Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr PreviousClosePrice()
     : value{ 0 } {}

    // constructor for PreviousClosePrice field
    constexpr explicit PreviousClosePrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PreviousClosePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PreviousClosePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
