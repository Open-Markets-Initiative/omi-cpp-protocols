#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Capacity of the order.
struct CustIndicator {

    static constexpr auto name = "Cust Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CustIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CustIndicator(const char &value)
     : value{ value } {}

    // get value of CustIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
