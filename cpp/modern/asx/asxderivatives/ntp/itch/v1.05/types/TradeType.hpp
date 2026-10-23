#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Nature of the match
struct TradeType {

    static constexpr auto name = "Trade Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradeType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeType(const char &value)
     : value{ value } {}

    // get value of TradeType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
