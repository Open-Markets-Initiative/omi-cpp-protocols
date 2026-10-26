#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Reference price for prelisted instruments or the last calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the session.
struct TradingReferencePriceEx {

    static constexpr const char* name = "Trading Reference Price Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr TradingReferencePriceEx()
     : value{ 0 } {}

    // constructor for TradingReferencePriceEx field
    constexpr explicit TradingReferencePriceEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of TradingReferencePriceEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of TradingReferencePriceEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
