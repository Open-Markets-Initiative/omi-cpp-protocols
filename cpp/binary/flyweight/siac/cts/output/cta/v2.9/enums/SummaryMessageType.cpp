#include "SummaryMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(SummaryMessageType value) {
    switch (value) {
        case SummaryMessageType::ConsolidatedStartOfDaySummaryMessage: return "Consolidated Start Of Day Summary Message";
        case SummaryMessageType::ParticipantStartOfDaySummaryMessage: return "Participant Start Of Day Summary Message";
        case SummaryMessageType::ConsolidatedEndOfDaySummaryMessage: return "Consolidated End Of Day Summary Message";
        case SummaryMessageType::ParticipantEndOfDaySummaryMessage: return "Participant End Of Day Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SummaryMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
