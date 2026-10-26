#include "MessageCategory.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(MessageCategory value) {
    switch (value) {
        case MessageCategory::Administrative: return "Administrative";
        case MessageCategory::Control: return "Control";
        case MessageCategory::MarketStatus: return "Market Status";
        case MessageCategory::Quote: return "Quote";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
