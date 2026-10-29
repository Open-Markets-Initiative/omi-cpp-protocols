#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Latest upper threshold price of the Auction Collar
struct AuctionCollarUpperThresholdPrice {

    static constexpr const char* name = "Auction Collar Upper Threshold Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr AuctionCollarUpperThresholdPrice()
     : value{ 0 } {}

    // constructor for AuctionCollarUpperThresholdPrice field
    constexpr explicit AuctionCollarUpperThresholdPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AuctionCollarUpperThresholdPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // does AuctionCollarUpperThresholdPrice hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of AuctionCollarUpperThresholdPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
