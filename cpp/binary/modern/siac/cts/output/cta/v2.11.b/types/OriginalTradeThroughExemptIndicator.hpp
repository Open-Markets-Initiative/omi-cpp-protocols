#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Original trade through exempt indicator
struct OriginalTradeThroughExemptIndicator {

    static constexpr auto name = "Original Trade Through Exempt Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalTradeThroughExemptIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalTradeThroughExemptIndicator(const char &value)
     : value{ value } {}

    // get value of OriginalTradeThroughExemptIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
