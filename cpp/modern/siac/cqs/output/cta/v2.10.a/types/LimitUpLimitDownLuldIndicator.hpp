#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Indicates the effect the Quote has on the Limit Up-Limit Down Price Band range
struct LimitUpLimitDownLuldIndicator {

    static constexpr auto name = "Limit Up Limit Down Luld Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LimitUpLimitDownLuldIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LimitUpLimitDownLuldIndicator(const char &value)
     : value{ value } {}

    // get value of LimitUpLimitDownLuldIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
