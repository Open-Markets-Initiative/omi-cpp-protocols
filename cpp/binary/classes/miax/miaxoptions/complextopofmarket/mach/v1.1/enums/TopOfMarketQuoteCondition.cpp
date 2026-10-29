#include "TopOfMarketQuoteCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(TopOfMarketQuoteCondition value) {
    switch (value) {
        case TopOfMarketQuoteCondition::Halted: return "Halted";
        case TopOfMarketQuoteCondition::Resumed: return "Resumed";
        case TopOfMarketQuoteCondition::Opened: return "Opened";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TopOfMarketQuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
