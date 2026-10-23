#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the Consolidated High/Low/Last Price applicable to the trade
struct ConsolidatedHighLowLastIndicator {

    static constexpr auto name = "Consolidated High Low Last Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ConsolidatedHighLowLastIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedHighLowLastIndicator(const char &value)
     : value{ value } {}

    // get value of ConsolidatedHighLowLastIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
