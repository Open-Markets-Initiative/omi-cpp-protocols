#include "InstrAttribType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

std::string_view to_string(InstrAttribType value) {
    switch (value) {
        case InstrAttribType::TradeTypeEligibility: return "Trade Type Eligibility";
        case InstrAttribType::GtdGtcEligibility: return "Gtd Gtc Eligibility";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrAttribType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
