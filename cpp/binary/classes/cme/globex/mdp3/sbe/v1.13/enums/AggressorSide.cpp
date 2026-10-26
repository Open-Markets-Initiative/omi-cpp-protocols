#include "AggressorSide.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(AggressorSide value) {
    switch (value) {
        case AggressorSide::NoAggressor: return "No Aggressor";
        case AggressorSide::Buy: return "Buy";
        case AggressorSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AggressorSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
