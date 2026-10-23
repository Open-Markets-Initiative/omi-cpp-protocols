#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Contains the FINRA ADF provided FINRA Best Bid Size associated with the FINRA Best Bid Price that had the FINRA Best Bid
struct FinraBestBidSize {

    static constexpr const char* name = "Finra Best Bid Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr FinraBestBidSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBestBidSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of FinraBestBidSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
