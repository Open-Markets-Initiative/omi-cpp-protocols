#include "ImpliedMarketIndicator.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(ImpliedMarketIndicator value) {
    switch (value) {
        case ImpliedMarketIndicator::NotImplied: return "Not Implied";
        case ImpliedMarketIndicator::ImpliedInOut: return "Implied In Out";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImpliedMarketIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
