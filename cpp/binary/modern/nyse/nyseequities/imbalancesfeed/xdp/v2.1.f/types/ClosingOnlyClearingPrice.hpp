#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// Closing only clearing price
struct ClosingOnlyClearingPrice {

    static constexpr const char* name = "Closing Only Clearing Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ClosingOnlyClearingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClosingOnlyClearingPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of ClosingOnlyClearingPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
