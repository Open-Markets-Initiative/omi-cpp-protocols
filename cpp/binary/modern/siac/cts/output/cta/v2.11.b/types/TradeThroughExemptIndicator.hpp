#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Denotes whether or not a trade is exempt (Rule 611)
struct TradeThroughExemptIndicator {

    static constexpr auto name = "Trade Through Exempt Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeThroughExemptIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeThroughExemptIndicator(const char &value)
     : value{ value } {}

    // get value of TradeThroughExemptIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
