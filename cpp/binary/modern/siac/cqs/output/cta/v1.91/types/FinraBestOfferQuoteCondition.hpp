#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Contains the FINRA ADF provided FINRA Best Offer Quote Condition associated with the Best FINRA Offer Price that had the FINRA Best Offer
struct FinraBestOfferQuoteCondition {

    static constexpr auto name = "Finra Best Offer Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FinraBestOfferQuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBestOfferQuoteCondition(const char &value)
     : value{ value } {}

    // get value of FinraBestOfferQuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
