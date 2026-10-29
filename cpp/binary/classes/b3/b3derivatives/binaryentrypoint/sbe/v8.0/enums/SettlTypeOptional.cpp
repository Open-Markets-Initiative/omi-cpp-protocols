#include "SettlTypeOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(SettlTypeOptional value) {
    switch (value) {
        case SettlTypeOptional::BuyersDiscretion: return "Buyers Discretion";
        case SettlTypeOptional::SellersDiscretion: return "Sellers Discretion";
        case SettlTypeOptional::Mutual: return "Mutual";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlTypeOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
