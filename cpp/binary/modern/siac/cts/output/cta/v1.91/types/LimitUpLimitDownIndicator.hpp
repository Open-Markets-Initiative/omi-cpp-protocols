#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Identifies the Limit Up-Limit Down action related to a security
struct LimitUpLimitDownIndicator {

    static constexpr auto name = "Limit Up Limit Down Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LimitUpLimitDownIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LimitUpLimitDownIndicator(const char &value)
     : value{ value } {}

    // get value of LimitUpLimitDownIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
