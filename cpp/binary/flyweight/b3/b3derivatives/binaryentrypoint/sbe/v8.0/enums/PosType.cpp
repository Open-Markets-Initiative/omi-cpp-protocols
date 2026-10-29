#include "PosType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(PosType value) {
    switch (value) {
        case PosType::TransactionQuantity: return "Transaction Quantity";
        case PosType::StartOfDayQty: return "Start Of Day Qty";
        case PosType::OptionExerciseQty: return "Option Exercise Qty";
        case PosType::BlockedQty: return "Blocked Qty";
        case PosType::UncoveredQty: return "Uncovered Qty";
        case PosType::CoveredQty: return "Covered Qty";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PosType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
