#include "SelfTradePreventionInstruction.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(SelfTradePreventionInstruction value) {
    switch (value) {
        case SelfTradePreventionInstruction::None: return "None";
        case SelfTradePreventionInstruction::CancelAggressorOrder: return "Cancel Aggressor Order";
        case SelfTradePreventionInstruction::CancelRestingOrder: return "Cancel Resting Order";
        case SelfTradePreventionInstruction::CancelBothOrders: return "Cancel Both Orders";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SelfTradePreventionInstruction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
