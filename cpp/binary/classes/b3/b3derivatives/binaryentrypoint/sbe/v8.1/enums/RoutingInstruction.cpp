#include "RoutingInstruction.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(RoutingInstruction value) {
    switch (value) {
        case RoutingInstruction::RetailLiquidityTaker: return "Retail Liquidity Taker";
        case RoutingInstruction::WaivedPriority: return "Waived Priority";
        case RoutingInstruction::BrokerOnly: return "Broker Only";
        case RoutingInstruction::BrokerOnlyRemoval: return "Broker Only Removal";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RoutingInstruction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
