#include "LegSide.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Buy: return "Buy";
        case LegSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
