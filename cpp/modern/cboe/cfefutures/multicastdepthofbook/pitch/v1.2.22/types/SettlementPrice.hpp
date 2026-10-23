#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Settlement Price
struct SettlementPrice {

    static constexpr const char* name = "Settlement Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr SettlementPrice()
     : value{ 0 } {}

    // constructor for SettlementPrice field
    constexpr explicit SettlementPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of SettlementPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of SettlementPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
