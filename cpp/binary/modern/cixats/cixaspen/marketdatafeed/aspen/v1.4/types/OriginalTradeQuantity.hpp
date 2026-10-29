#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Quantity of the trade being corrected
struct OriginalTradeQuantity {

    static constexpr const char* name = "Original Trade Quantity";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalTradeQuantity()
     : value{ 0 } {}

    // constructor for OriginalTradeQuantity field
    constexpr explicit OriginalTradeQuantity(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of OriginalTradeQuantity field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of OriginalTradeQuantity field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
