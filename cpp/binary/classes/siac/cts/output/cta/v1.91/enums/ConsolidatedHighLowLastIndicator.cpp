#include "ConsolidatedHighLowLastIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(ConsolidatedHighLowLastIndicator value) {
    switch (value) {
        case ConsolidatedHighLowLastIndicator::None: return "None";
        case ConsolidatedHighLowLastIndicator::High: return "High";
        case ConsolidatedHighLowLastIndicator::Low: return "Low";
        case ConsolidatedHighLowLastIndicator::Last: return "Last";
        case ConsolidatedHighLowLastIndicator::HighLast: return "High Last";
        case ConsolidatedHighLowLastIndicator::LowLast: return "Low Last";
        case ConsolidatedHighLowLastIndicator::HighLowLast: return "High Low Last";
        case ConsolidatedHighLowLastIndicator::HighLow: return "High Low";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ConsolidatedHighLowLastIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
