#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// tradingReferencePrice
struct TradingReferencePriceOptional {

    static constexpr const char* name = "Trading Reference Price Optional";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr TradingReferencePriceOptional()
     : value{ 0 } {}

    // constructor for TradingReferencePriceOptional field
    constexpr explicit TradingReferencePriceOptional(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TradingReferencePriceOptional field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TradingReferencePriceOptional field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
