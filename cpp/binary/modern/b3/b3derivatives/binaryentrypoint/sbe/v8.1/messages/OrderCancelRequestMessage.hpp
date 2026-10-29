#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../types/Side.hpp"
#include "../types/SingleCancelRestatementReason.hpp"
#include "../types/Offset54Padding2.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTraderOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// OrderCancelRequestMessage
struct OrderCancelRequestMessage {

    InboundBusinessHeader inbound_business_header;
    Offset18Padding2 offset_18_padding_2;
    Clordid clordid;
    SecurityId security_id;
    OrderIdOptional order_id_optional;
    Origclordid origclordid;
    Side side;
    SingleCancelRestatementReason single_cancel_restatement_reason;
    Offset54Padding2 offset_54_padding_2;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTraderOptional executing_trader_optional;

    // parse method
    static OrderCancelRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelRequestMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
