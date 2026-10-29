#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Indicates the affect the Quote has on the Limit Up-Limit Down Price Band range.
struct LuldIndicator {

    static constexpr auto name = "Luld Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LuldIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LuldIndicator(const char &value)
     : value{ value } {}

    // get value of LuldIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
