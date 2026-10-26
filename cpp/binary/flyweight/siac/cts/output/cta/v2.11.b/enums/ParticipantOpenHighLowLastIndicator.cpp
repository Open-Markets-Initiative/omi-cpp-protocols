#include "ParticipantOpenHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(ParticipantOpenHighLowLastIndicator value) {
    switch (value) {
        case ParticipantOpenHighLowLastIndicator::None: return "None";
        case ParticipantOpenHighLowLastIndicator::High: return "High";
        case ParticipantOpenHighLowLastIndicator::Low: return "Low";
        case ParticipantOpenHighLowLastIndicator::Last: return "Last";
        case ParticipantOpenHighLowLastIndicator::HighLast: return "High Last";
        case ParticipantOpenHighLowLastIndicator::LowLast: return "Low Last";
        case ParticipantOpenHighLowLastIndicator::Unused: return "Unused";
        case ParticipantOpenHighLowLastIndicator::Open: return "Open";
        case ParticipantOpenHighLowLastIndicator::OpenHigh: return "Open High";
        case ParticipantOpenHighLowLastIndicator::OpenLow: return "Open Low";
        case ParticipantOpenHighLowLastIndicator::OpenHighLowLast: return "Open High Low Last";
        case ParticipantOpenHighLowLastIndicator::OpenLast: return "Open Last";
        case ParticipantOpenHighLowLastIndicator::OpenHighLow: return "Open High Low";
        case ParticipantOpenHighLowLastIndicator::OpenHighLast: return "Open High Last";
        case ParticipantOpenHighLowLastIndicator::OpenLowLast: return "Open Low Last";
        case ParticipantOpenHighLowLastIndicator::HighLow: return "High Low";
        case ParticipantOpenHighLowLastIndicator::HighLowLast: return "High Low Last";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ParticipantOpenHighLowLastIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
