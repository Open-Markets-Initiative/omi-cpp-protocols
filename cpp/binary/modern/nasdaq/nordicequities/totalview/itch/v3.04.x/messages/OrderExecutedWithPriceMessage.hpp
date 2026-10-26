#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/Printable.hpp"
#include "../types/TradePrice.hpp"
#include "../types/MpidOwner.hpp"
#include "../types/MpidCounterparty.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order executed at a price different to its display price
struct OrderExecutedWithPriceMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderReferenceNumber order_reference_number;
    ExecutedQuantity executed_quantity;
    MatchNumber match_number;
    Printable printable;
    TradePrice trade_price;
    MpidOwner mpid_owner;
    MpidCounterparty mpid_counterparty;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static OrderExecutedWithPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedWithPriceMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedWithPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedWithPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedWithPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedWithPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
