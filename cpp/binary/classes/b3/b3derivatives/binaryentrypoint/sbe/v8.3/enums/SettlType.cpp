#include "SettlType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(SettlType value) {
    switch (value) {
        case SettlType::BuyersDiscretion: return "Buyers Discretion";
        case SettlType::SellersDiscretion: return "Sellers Discretion";
        case SettlType::Mutual: return "Mutual";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
