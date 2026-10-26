#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::iextp::v1_01 {

// Trading status identifier
enum class TradingStatus : char {
    TradingHaltedAcrossAllUsEquityMarkets = 'H',               // Trading Halted Across All Us Equity Markets
    TradingHaltReleasedIntoAnOrderAcceptancePeriodOnIex = 'O', // Trading Halt Released Into An Order Acceptance Period On Iex
    TradingPausedAndOrderAcceptancePeriodOnIex = 'P',          // Trading Paused And Order Acceptance Period On Iex
    TradingOnIex = 'T',                                        // Trading On Iex
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace iex::iexequities::deepplus::iextp::v1_01
