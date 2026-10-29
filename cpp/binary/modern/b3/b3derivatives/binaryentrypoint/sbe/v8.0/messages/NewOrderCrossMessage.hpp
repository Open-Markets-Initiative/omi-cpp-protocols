#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/Crossid.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTraderOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderQty.hpp"
#include "../types/Price.hpp"
#include "../types/CrossedIndicator.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// NewOrderCrossMessage
struct NewOrderCrossMessage {

    InboundBusinessHeader inbound_business_header;
    Offset18Padding2 offset_18_padding_2;
    Crossid crossid;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTraderOptional executing_trader_optional;
    SecurityId security_id;
    OrderQty order_qty;
    Price price;
    CrossedIndicator crossed_indicator;

    // parse method
    static NewOrderCrossMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NewOrderCrossMessage*>(buffer);
    }

    // parse method const
    static const NewOrderCrossMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NewOrderCrossMessage*>(buffer);
    }
};

#pragma pack(pop)
}
