#include "EquityAndIndexEndOfDaySummaryMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(EquityAndIndexEndOfDaySummaryMessageType value) {
    switch (value) {
        case EquityAndIndexEndOfDaySummaryMessageType::EquityAndIndexEndOfDaySummary: return "Equity And Index End Of Day Summary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EquityAndIndexEndOfDaySummaryMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
