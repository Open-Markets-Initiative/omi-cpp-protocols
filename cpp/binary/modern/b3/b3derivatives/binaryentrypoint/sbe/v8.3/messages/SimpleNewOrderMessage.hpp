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
#include "../types/SimpleOrdtype.hpp"
#include "../types/TimeInForceSimple.hpp"
#include "../types/RoutingInstruction.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// SimpleNewOrderMessage
struct SimpleNewOrderMessage {

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
    SimpleOrdtype simple_ordtype;
    TimeInForceSimple time_in_force_simple;
    RoutingInstruction routing_instruction;
    OrderQty order_qty;
    PriceOptional price_optional;
    InvestorId investor_id;

    // parse method
    static SimpleNewOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleNewOrderMessage*>(buffer);
    }

    // parse method const
    static const SimpleNewOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleNewOrderMessage*>(buffer);
    }
};

#pragma pack(pop)
}
