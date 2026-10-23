#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies the trading status applicable to the instrument
enum class WorkupTradingStatus : std::uint8_t {
    ReadyToTrade = 17,           // Ready To Trade
    NotAvailableForTrading = 18, // Not Available For Trading
    PrivateWorkup = 201,         // Private Workup
    PublicWorkup = 202,          // Public Workup
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(WorkupTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, WorkupTradingStatus value);

} // namespace cme::globex::mdp3::sbe::v1_13
