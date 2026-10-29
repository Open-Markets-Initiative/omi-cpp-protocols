#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Contains the FINRA ADF provided FINRA Best Bid Price that is the FINRA Best Bid (FBBO
struct FinraBestBidQuoteCondition {

    static constexpr auto name = "Finra Best Bid Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FinraBestBidQuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBestBidQuoteCondition(const char &value)
     : value{ value } {}

    // get value of FinraBestBidQuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
