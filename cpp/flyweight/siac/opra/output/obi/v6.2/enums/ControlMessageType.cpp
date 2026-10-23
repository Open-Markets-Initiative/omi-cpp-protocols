#include "ControlMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(ControlMessageType value) {
    switch (value) {
        case ControlMessageType::StartOfDay: return "Start Of Day";
        case ControlMessageType::StartOfSummary: return "Start Of Summary";
        case ControlMessageType::EndOfSummary: return "End Of Summary";
        case ControlMessageType::EndOfDay: return "End Of Day";
        case ControlMessageType::ResetBlockSequenceNumber: return "Reset Block Sequence Number";
        case ControlMessageType::StartOfOpenInterest: return "Start Of Open Interest";
        case ControlMessageType::EndOfOpenInterest: return "End Of Open Interest";
        case ControlMessageType::LineIntegrity: return "Line Integrity";
        case ControlMessageType::DisasterRecoveryDataCenterActivation: return "Disaster Recovery Data Center Activation";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ControlMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
