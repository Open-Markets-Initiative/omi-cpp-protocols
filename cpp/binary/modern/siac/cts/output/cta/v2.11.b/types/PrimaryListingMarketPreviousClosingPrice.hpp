#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the previous closing price for the primary listing market. Has implied 6 decimal places
struct PrimaryListingMarketPreviousClosingPrice {

    static constexpr const char* name = "Primary Listing Market Previous Closing Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr PrimaryListingMarketPreviousClosingPrice()
     : value{ 0 } {}

    // constructor for PrimaryListingMarketPreviousClosingPrice field
    constexpr explicit PrimaryListingMarketPreviousClosingPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PrimaryListingMarketPreviousClosingPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PrimaryListingMarketPreviousClosingPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
