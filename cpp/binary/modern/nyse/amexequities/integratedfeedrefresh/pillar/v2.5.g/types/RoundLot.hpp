#pragma once

#include <cstddef>

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {


// Round Lots Accepted: Y - Yes, N - No.
struct RoundLot {

    static constexpr auto name = "Round Lot";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RoundLot()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RoundLot(const char &value)
     : value{ value } {}

    // get value of RoundLot field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
