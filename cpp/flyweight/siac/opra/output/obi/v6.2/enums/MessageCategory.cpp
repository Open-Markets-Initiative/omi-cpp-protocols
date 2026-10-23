#include "MessageCategory.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(MessageCategory value) {
    switch (value) {
        case MessageCategory::Administrative: return "Administrative";
        case MessageCategory::Control: return "Control";
        case MessageCategory::EquityAndIndexLastSale: return "Equity And Index Last Sale";
        case MessageCategory::OpenInterest: return "Open Interest";
        case MessageCategory::EquityAndIndexEndOfDaySummary: return "Equity And Index End Of Day Summary";
        case MessageCategory::LongEquityAndIndexQuote: return "Long Equity And Index Quote";
        case MessageCategory::ShortEquityAndIndexQuote: return "Short Equity And Index Quote";
        case MessageCategory::UnderlyingValue: return "Underlying Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
