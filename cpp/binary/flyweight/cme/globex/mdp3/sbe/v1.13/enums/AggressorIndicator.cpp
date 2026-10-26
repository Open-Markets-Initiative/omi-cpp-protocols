#include "AggressorIndicator.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(AggressorIndicator value) {
    switch (value) {
        case AggressorIndicator::NotAggressor: return "Not Aggressor";
        case AggressorIndicator::Aggressor: return "Aggressor";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AggressorIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
