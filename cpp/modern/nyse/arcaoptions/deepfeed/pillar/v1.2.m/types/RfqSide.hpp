#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Side of the RFQ.
struct RfqSide {

    static constexpr auto name = "Rfq Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RfqSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RfqSide(const char &value)
     : value{ value } {}

    // get value of RfqSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
