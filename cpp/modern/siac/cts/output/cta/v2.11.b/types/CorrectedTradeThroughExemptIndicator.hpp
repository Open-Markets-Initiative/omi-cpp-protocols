#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Corrected trade through exempt indicator
struct CorrectedTradeThroughExemptIndicator {

    static constexpr auto name = "Corrected Trade Through Exempt Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedTradeThroughExemptIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedTradeThroughExemptIndicator(const char &value)
     : value{ value } {}

    // get value of CorrectedTradeThroughExemptIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
