#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// “H” = MIAX has halted trading for this Underlying Symbol, “R” = MIAX will resume trading (reopen) for this Underlying Symbol, “O” = MIAX will open trading for this Underlying Symbol
struct TradingStatus {

    static constexpr auto name = "Trading Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingStatus(const char &value)
     : value{ value } {}

    // get value of TradingStatus field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
