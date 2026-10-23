#include "MoneyOrPar.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(MoneyOrPar value) {
    switch (value) {
        case MoneyOrPar::Money: return "Money";
        case MoneyOrPar::Par: return "Par";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MoneyOrPar value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
