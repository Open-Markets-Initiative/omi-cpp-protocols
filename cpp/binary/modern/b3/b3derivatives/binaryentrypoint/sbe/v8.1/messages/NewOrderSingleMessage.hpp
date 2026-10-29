#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/MmProtectionReset.hpp"
#include "../types/Clordid.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/SelfTradePreventionInstruction.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Side.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/RoutingInstruction.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/ExecutingTraderOptional.hpp"
#include "../types/ExpireDate.hpp"
#include "../structs/CustodianInfo.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/StrategyId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// NewOrderSingleMessage
struct NewOrderSingleMessage {

    InboundBusinessHeader inbound_business_header;
    Ordtagid ordtagid;
    MmProtectionReset mm_protection_reset;
    Clordid clordid;
    Account account;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    SelfTradePreventionInstruction self_trade_prevention_instruction;
    SecurityId security_id;
    Side side;
    Ordtype ordtype;
    TimeInForce time_in_force;
    RoutingInstruction routing_instruction;
    OrderQty order_qty;
    PriceOptional price_optional;
    StopPx stop_px;
    MinQty min_qty;
    MaxFloor max_floor;
    ExecutingTraderOptional executing_trader_optional;
    ExpireDate expire_date;
    CustodianInfo custodian_info;
    InvestorId investor_id;
    StrategyId strategy_id;

    // parse method
    static NewOrderSingleMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NewOrderSingleMessage*>(buffer);
    }

    // parse method const
    static const NewOrderSingleMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NewOrderSingleMessage*>(buffer);
    }
};

#pragma pack(pop)
}
