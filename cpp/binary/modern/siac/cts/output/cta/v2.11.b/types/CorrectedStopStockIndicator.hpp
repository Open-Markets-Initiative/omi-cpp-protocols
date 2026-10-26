#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Corrected stop stock indicator
struct CorrectedStopStockIndicator {

    static constexpr auto name = "Corrected Stop Stock Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedStopStockIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedStopStockIndicator(const char &value)
     : value{ value } {}

    // get value of CorrectedStopStockIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
