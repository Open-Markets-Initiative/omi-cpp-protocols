#include "ControlMessageType.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(ControlMessageType value) {
    switch (value) {
        case ControlMessageType::StartOfDay: return "Start Of Day";
        case ControlMessageType::FinraClose: return "Finra Close";
        case ControlMessageType::ResetBlockSequenceNumber: return "Reset Block Sequence Number";
        case ControlMessageType::FinraOpen: return "Finra Open";
        case ControlMessageType::DisasterRecoveryDataCenterActivation: return "Disaster Recovery Data Center Activation";
        case ControlMessageType::LineIntegrity: return "Line Integrity";
        case ControlMessageType::EndOfDay: return "End Of Day";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ControlMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
