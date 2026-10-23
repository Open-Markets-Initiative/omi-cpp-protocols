#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies the reason for the status change
enum class HaltReason : std::uint8_t {
    GroupSchedule = 0,            // Group Schedule
    SurveillanceIntervention = 1, // Surveillance Intervention
    MarketEvent = 2,              // Market Event
    InstrumentActivation = 3,     // Instrument Activation
    InstrumentExpiration = 4,     // Instrument Expiration
    Unknown = 5,                  // Unknown
    RecoveryInProcess = 6,        // Recovery In Process
    TradeDateRoll = 7,            // Trade Date Roll
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HaltReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HaltReason value);

} // namespace cme::globex::mdp3::sbe::v1_13
