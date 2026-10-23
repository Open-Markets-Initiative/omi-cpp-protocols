#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Original stop stock indicator
struct OriginalStopStockIndicator {

    static constexpr auto name = "Original Stop Stock Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalStopStockIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalStopStockIndicator(const char &value)
     : value{ value } {}

    // get value of OriginalStopStockIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
