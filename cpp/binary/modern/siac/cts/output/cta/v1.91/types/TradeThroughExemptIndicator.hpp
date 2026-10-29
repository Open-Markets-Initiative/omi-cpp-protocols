#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Denotes whether or not a trade is exempt (Rule 611) and when used jointly with certain Sale Conditions, will more fully describe the characteristics of a particular trade
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
