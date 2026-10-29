#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// execRestatementReason
enum class ExecRestatementReason : std::uint8_t {
    MarketOption = 8,                                       // Market Option
    CancelOnHardDisconnection = 100,                        // Cancel On Hard Disconnection
    CancelOnTerminate = 101,                                // Cancel On Terminate
    CancelOnDisconnectAndTerminate = 102,                   // Cancel On Disconnect And Terminate
    SelfTradingPrevention = 103,                            // Self Trading Prevention
    CancelFromFirmsoft = 105,                               // Cancel From Firmsoft
    CancelRestingOrderOnSelfTrade = 107,                    // Cancel Resting Order On Self Trade
    MarketMakerProtection = 200,                            // Market Maker Protection
    RiskManagementCancellation = 201,                       // Risk Management Cancellation
    OrderMassActionFromClientRequest = 202,                 // Order Mass Action From Client Request
    CancelOrderDueToOperationalError = 203,                 // Cancel Order Due To Operational Error
    OrderCancelledDueToOperationalError = 204,              // Order Cancelled Due To Operational Error
    CancelOrderFirmsoftDueToOperationalError = 205,         // Cancel Order Firmsoft Due To Operational Error
    OrderCancelledFirmsoftDueToOperationalError = 206,      // Order Cancelled Firmsoft Due To Operational Error
    MassCancelOrderDueToOperationalErrorRequest = 207,      // Mass Cancel Order Due To Operational Error Request
    MassCancelOrderDueToOperationalErrorEffective = 208,    // Mass Cancel Order Due To Operational Error Effective
    CancelMinimumQtyBlock = 209,                            // Cancel Minimum Qty Block
    CancelRemainingFromSweepCross = 210,                    // Cancel Remaining From Sweep Cross
    MassCancelOnBehalf = 211,                               // Mass Cancel On Behalf
    MassCancelOnBehalfDueToOperationalErrorEffective = 212, // Mass Cancel On Behalf Due To Operational Error Effective
    CancelOnMidpointBrokerOnlyRemoval = 213,                // Cancel On Midpoint Broker Only Removal
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExecRestatementReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExecRestatementReason value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
