#include "ControlMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(ControlMessageType value) {
    switch (value) {
        case ControlMessageType::StartOfDayMessage: return "Start Of Day Message";
        case ControlMessageType::ResetBlockSequenceNumberMessage: return "Reset Block Sequence Number Message";
        case ControlMessageType::DisasterRecoveryDataCenterActivationMessage: return "Disaster Recovery Data Center Activation Message";
        case ControlMessageType::LineIntegrityMessage: return "Line Integrity Message";
        case ControlMessageType::EndOfDayMessage: return "End Of Day Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ControlMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
