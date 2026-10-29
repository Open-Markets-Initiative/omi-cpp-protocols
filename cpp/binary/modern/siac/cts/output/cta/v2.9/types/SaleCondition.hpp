#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Denotes the sale condition associated with a trade
struct SaleCondition {

    static constexpr auto name = "Sale Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SaleCondition(const char &value)
     : value{ value } {}

    // get value of SaleCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
