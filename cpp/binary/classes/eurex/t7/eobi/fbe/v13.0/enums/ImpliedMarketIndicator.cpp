#include "ImpliedMarketIndicator.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

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

} // namespace eurex::t7::eobi::fbe::v13_0
