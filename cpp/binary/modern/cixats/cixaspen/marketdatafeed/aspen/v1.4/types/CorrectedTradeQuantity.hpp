#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Quantity the trade is being amended/corrected to
struct CorrectedTradeQuantity {

    static constexpr const char* name = "Corrected Trade Quantity";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr CorrectedTradeQuantity()
     : value{ 0 } {}

    // constructor for CorrectedTradeQuantity field
    constexpr explicit CorrectedTradeQuantity(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of CorrectedTradeQuantity field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of CorrectedTradeQuantity field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
