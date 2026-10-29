#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The previous day’s Settlement Price
struct SettlementPrice {

    static constexpr const char* name = "Settlement Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr SettlementPrice()
     : value{ 0 } {}

    // constructor for SettlementPrice field
    constexpr explicit SettlementPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of SettlementPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of SettlementPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
