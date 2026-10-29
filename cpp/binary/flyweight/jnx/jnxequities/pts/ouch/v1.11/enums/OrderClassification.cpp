#include "OrderClassification.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(OrderClassification value) {
    switch (value) {
        case OrderClassification::NonHft: return "Non Hft";
        case OrderClassification::HftMarketMakingStrategy: return "Hft Market Making Strategy";
        case OrderClassification::HftArbitrageStrategy: return "Hft Arbitrage Strategy";
        case OrderClassification::HftDirectionalStrategy: return "Hft Directional Strategy";
        case OrderClassification::HftOtherStrategy: return "Hft Other Strategy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderClassification value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
