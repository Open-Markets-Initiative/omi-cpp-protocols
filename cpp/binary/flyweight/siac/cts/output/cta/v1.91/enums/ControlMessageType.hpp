#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Control message type
enum class ControlMessageType : char {
    StartOfDayMessage = 'A',                           // Start Of Day Message
    ResetBlockSequenceNumberMessage = 'L',             // Reset Block Sequence Number Message
    StartOfTestCycleMessage = 'M',                     // Start Of Test Cycle Message
    EndOfTestCycleMessage = 'N',                       // End Of Test Cycle Message
    DisasterRecoveryDataCenterActivationMessage = 'P', // Disaster Recovery Data Center Activation Message
    LineIntegrityMessage = 'T',                        // Line Integrity Message
    EndOfDayMessage = 'Z',                             // End Of Day Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ControlMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ControlMessageType value);

} // namespace siac::cts::output::cta::v1_91
