#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies whether the transaction constituted a stopped order
struct StopStockIndicator {

    static constexpr auto name = "Stop Stock Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr StopStockIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StopStockIndicator(const char &value)
     : value{ value } {}

    // get value of StopStockIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
