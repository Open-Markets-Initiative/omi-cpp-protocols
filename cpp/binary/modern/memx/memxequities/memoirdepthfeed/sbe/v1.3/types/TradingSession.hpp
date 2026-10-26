#pragma once

#include <cstddef>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// TradingSession
struct TradingSession {

    static constexpr auto name = "Trading Session";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TradingSession()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSession(const char &value)
     : value{ value } {}

    // get value of TradingSession field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
