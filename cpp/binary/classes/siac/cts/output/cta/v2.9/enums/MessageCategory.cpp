#include "MessageCategory.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(MessageCategory value) {
    switch (value) {
        case MessageCategory::Administrative: return "Administrative";
        case MessageCategory::Control: return "Control";
        case MessageCategory::Indices: return "Indices";
        case MessageCategory::MarketStatus: return "Market Status";
        case MessageCategory::PriorDay: return "Prior Day";
        case MessageCategory::Summary: return "Summary";
        case MessageCategory::Trade: return "Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
