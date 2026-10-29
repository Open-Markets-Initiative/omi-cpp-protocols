#include "AssetClass.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(AssetClass value) {
    switch (value) {
        case AssetClass::Equity: return "Equity";
        case AssetClass::FixedIncome: return "Fixed Income";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AssetClass value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
