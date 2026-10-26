#include "SettlPriceType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(SettlPriceType value) {
    switch (value) {
        case SettlPriceType::Final: return "Final";
        case SettlPriceType::Theoretical: return "Theoretical";
        case SettlPriceType::Updated: return "Updated";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlPriceType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
