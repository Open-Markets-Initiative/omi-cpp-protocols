#include "Ordtype.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(Ordtype value) {
    switch (value) {
        case Ordtype::Market: return "Market";
        case Ordtype::Limit: return "Limit";
        case Ordtype::StopLoss: return "Stop Loss";
        case Ordtype::StopLimit: return "Stop Limit";
        case Ordtype::MarketWithLeftoverAsLimit: return "Market With Leftover As Limit";
        case Ordtype::Rlp: return "Rlp";
        case Ordtype::PeggedMidpoint: return "Pegged Midpoint";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Ordtype value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
