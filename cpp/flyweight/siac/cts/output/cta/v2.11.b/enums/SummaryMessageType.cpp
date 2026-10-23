#include "SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(SummaryMessageType value) {
    switch (value) {
        case SummaryMessageType::ConsolidatedStartOfDaySummary: return "Consolidated Start Of Day Summary";
        case SummaryMessageType::ParticipantStartOfDaySummary: return "Participant Start Of Day Summary";
        case SummaryMessageType::ConsolidatedEndOfDaySummary: return "Consolidated End Of Day Summary";
        case SummaryMessageType::FractionalConsolidatedEndOfDaySummary: return "Fractional Consolidated End Of Day Summary";
        case SummaryMessageType::ParticipantEndOfDaySummary: return "Participant End Of Day Summary";
        case SummaryMessageType::FractionalParticipantEndOfDaySummary: return "Fractional Participant End Of Day Summary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SummaryMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
