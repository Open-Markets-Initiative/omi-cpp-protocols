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
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// SimpleModifyOrderMessage
struct SimpleModifyOrderMessage {

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
    OrderIdOptional order_id_optional;
    Origclordid origclordid;
    InvestorId investor_id;

    // parse method
    static SimpleModifyOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleModifyOrderMessage*>(buffer);
    }

    // parse method const
    static const SimpleModifyOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleModifyOrderMessage*>(buffer);
    }
};

#pragma pack(pop)
}
