#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// tradingReferencePrice
struct TradingReferencePriceLegacy {

    static constexpr const char* name = "Trading Reference Price Legacy";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr TradingReferencePriceLegacy()
     : value{ 0 } {}

    // constructor for TradingReferencePriceLegacy field
    constexpr explicit TradingReferencePriceLegacy(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TradingReferencePriceLegacy field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TradingReferencePriceLegacy field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
