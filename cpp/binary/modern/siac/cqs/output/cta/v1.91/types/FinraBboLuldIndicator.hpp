#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Indicates the affect that the Limit Up-Limit Down Price Bands have on the FINRA Best Bid and FINRA Best Offer
struct FinraBboLuldIndicator {

    static constexpr auto name = "Finra Bbo Luld Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FinraBboLuldIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBboLuldIndicator(const char &value)
     : value{ value } {}

    // get value of FinraBboLuldIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
