#pragma once

#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// C1 Only. H = Halted, Q = Quote-Only, R = Opening Rotation, T = Trading.
struct GthTradingStatus {

    static constexpr auto name = "Gth Trading Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr GthTradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit GthTradingStatus(const char &value)
     : value{ value } {}

    // get value of GthTradingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
