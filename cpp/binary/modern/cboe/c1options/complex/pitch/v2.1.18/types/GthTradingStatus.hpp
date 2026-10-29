#pragma once

#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// GTH Trading Status (C1 Only)
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
