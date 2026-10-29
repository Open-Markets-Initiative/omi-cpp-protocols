#include "OrderCategory.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(OrderCategory value) {
    switch (value) {
        case OrderCategory::ResultOfOptionsExercise: return "Result Of Options Exercise";
        case OrderCategory::ResultOfAssignmentFromAnOptionsExercise: return "Result Of Assignment From An Options Exercise";
        case OrderCategory::ResultOfAutomaticOptionsExercise: return "Result Of Automatic Options Exercise";
        case OrderCategory::ResultOfMidpointOrder: return "Result Of Midpoint Order";
        case OrderCategory::ResultOfBlockBookTrade: return "Result Of Block Book Trade";
        case OrderCategory::ResultOfTradeAtClose: return "Result Of Trade At Close";
        case OrderCategory::ResultOfTradeAtAverage: return "Result Of Trade At Average";
        case OrderCategory::ImpliedOrder: return "Implied Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderCategory value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
