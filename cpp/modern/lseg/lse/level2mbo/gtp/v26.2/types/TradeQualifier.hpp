#pragma once

#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Qualifier of the trade.
struct TradeQualifier {

    static constexpr auto name = "Trade Qualifier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeQualifier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeQualifier(const char &value)
     : value{ value } {}

    // get value of TradeQualifier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
