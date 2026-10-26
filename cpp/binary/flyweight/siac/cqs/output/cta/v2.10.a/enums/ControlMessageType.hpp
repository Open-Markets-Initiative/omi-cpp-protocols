#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the type of Control message
enum class ControlMessageType : char {
    StartOfDay = 'A',                           // Start Of Day
    FinraClose = 'C',                           // Finra Close
    ResetBlockSequenceNumber = 'L',             // Reset Block Sequence Number
    FinraOpen = 'O',                            // Finra Open
    DisasterRecoveryDataCenterActivation = 'P', // Disaster Recovery Data Center Activation
    LineIntegrity = 'T',                        // Line Integrity
    EndOfDay = 'Z',                             // End Of Day
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ControlMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ControlMessageType value);

} // namespace siac::cqs::output::cta::v2_10_a
