#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Indicates the affect that the Limit Up-Limit Down Price Band changes have on the National Best Bid and National Best Offer
struct NationalBboLuldIndicator {

    static constexpr auto name = "National Bbo Luld Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr NationalBboLuldIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NationalBboLuldIndicator(const char &value)
     : value{ value } {}

    // get value of NationalBboLuldIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
