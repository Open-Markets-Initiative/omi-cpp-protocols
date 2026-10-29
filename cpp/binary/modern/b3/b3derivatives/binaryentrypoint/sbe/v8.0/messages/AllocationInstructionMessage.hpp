#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/AllocId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AllocTransType.hpp"
#include "../types/AllocType.hpp"
#include "../types/AllocNoOrdersType.hpp"
#include "../types/Quantity.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeDateOptional.hpp"
#include "../types/IndividualAllocId.hpp"
#include "../types/AllocAccount.hpp"
#include "../types/AllocQty.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// AllocationInstructionMessage
struct AllocationInstructionMessage {

    InboundBusinessHeader inbound_business_header;
    AllocId alloc_id;
    SecurityId security_id;
    AllocTransType alloc_trans_type;
    AllocType alloc_type;
    AllocNoOrdersType alloc_no_orders_type;
    Quantity quantity;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    TradeId trade_id;
    TradeDateOptional trade_date_optional;
    IndividualAllocId individual_alloc_id;
    AllocAccount alloc_account;
    AllocQty alloc_qty;

    // parse method
    static AllocationInstructionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AllocationInstructionMessage*>(buffer);
    }

    // parse method const
    static const AllocationInstructionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AllocationInstructionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
