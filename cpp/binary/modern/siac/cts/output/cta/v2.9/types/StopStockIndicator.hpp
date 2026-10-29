#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// The transaction that constituted the trade-through was the execution by a trading center of an order for which, at the time of receipt of the order, the trading center had guaranteed an execution at no worse than a specified price
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
