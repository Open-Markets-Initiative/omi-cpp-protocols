#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Control Message Type
enum class ControlMessageType : char {
    StartOfDay = 'C',                           // Start Of Day
    StartOfSummary = 'E',                       // Start Of Summary
    EndOfSummary = 'F',                         // End Of Summary
    EndOfDay = 'J',                             // End Of Day
    ResetBlockSequenceNumber = 'K',             // Reset Block Sequence Number
    StartOfOpenInterest = 'L',                  // Start Of Open Interest
    EndOfOpenInterest = 'M',                    // End Of Open Interest
    LineIntegrity = 'N',                        // Line Integrity
    DisasterRecoveryDataCenterActivation = 'P', // Disaster Recovery Data Center Activation
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ControlMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ControlMessageType value);

} // namespace siac::opra::output::obi::v6_2
