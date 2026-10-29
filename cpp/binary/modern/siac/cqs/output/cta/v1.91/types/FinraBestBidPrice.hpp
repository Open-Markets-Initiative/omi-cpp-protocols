#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Contains the FINRA ADF provided FINRA Best Bid Price that is the FINRA Best Bid (FBBO
struct FinraBestBidPrice {

    static constexpr const char* name = "Finra Best Bid Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr FinraBestBidPrice()
     : value{ 0 } {}

    // constructor for FinraBestBidPrice field
    constexpr explicit FinraBestBidPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of FinraBestBidPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of FinraBestBidPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
