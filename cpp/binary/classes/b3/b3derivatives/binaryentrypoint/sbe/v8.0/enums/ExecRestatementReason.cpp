#include "ExecRestatementReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(ExecRestatementReason value) {
    switch (value) {
        case ExecRestatementReason::MarketOption: return "Market Option";
        case ExecRestatementReason::CancelOnHardDisconnection: return "Cancel On Hard Disconnection";
        case ExecRestatementReason::CancelOnTerminate: return "Cancel On Terminate";
        case ExecRestatementReason::CancelOnDisconnectAndTerminate: return "Cancel On Disconnect And Terminate";
        case ExecRestatementReason::SelfTradingPrevention: return "Self Trading Prevention";
        case ExecRestatementReason::CancelFromFirmsoft: return "Cancel From Firmsoft";
        case ExecRestatementReason::CancelRestingOrderOnSelfTrade: return "Cancel Resting Order On Self Trade";
        case ExecRestatementReason::MarketMakerProtection: return "Market Maker Protection";
        case ExecRestatementReason::RiskManagementCancellation: return "Risk Management Cancellation";
        case ExecRestatementReason::OrderMassActionFromClientRequest: return "Order Mass Action From Client Request";
        case ExecRestatementReason::CancelOrderDueToOperationalError: return "Cancel Order Due To Operational Error";
        case ExecRestatementReason::OrderCancelledDueToOperationalError: return "Order Cancelled Due To Operational Error";
        case ExecRestatementReason::CancelOrderFirmsoftDueToOperationalError: return "Cancel Order Firmsoft Due To Operational Error";
        case ExecRestatementReason::OrderCancelledFirmsoftDueToOperationalError: return "Order Cancelled Firmsoft Due To Operational Error";
        case ExecRestatementReason::MassCancelOrderDueToOperationalErrorRequest: return "Mass Cancel Order Due To Operational Error Request";
        case ExecRestatementReason::MassCancelOrderDueToOperationalErrorEffective: return "Mass Cancel Order Due To Operational Error Effective";
        case ExecRestatementReason::CancelOnMidpointBrokerOnlyRemoval: return "Cancel On Midpoint Broker Only Removal";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExecRestatementReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
