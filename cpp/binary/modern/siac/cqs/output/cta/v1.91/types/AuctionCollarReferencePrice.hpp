#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// Price used by the exchange to establish the Auction Collar
struct AuctionCollarReferencePrice {

    static constexpr const char* name = "Auction Collar Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr AuctionCollarReferencePrice()
     : value{ 0 } {}

    // constructor for AuctionCollarReferencePrice field
    constexpr explicit AuctionCollarReferencePrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AuctionCollarReferencePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // does AuctionCollarReferencePrice hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of AuctionCollarReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
