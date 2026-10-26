#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchId.hpp"
#include "../types/ComboGroupId.hpp"
#include "../types/OwnerParticipantId.hpp"
#include "../types/CounterpartyParticipantId.hpp"
#include "../types/TradePrice.hpp"
#include "../types/OccurredAtCross.hpp"
#include "../types/Printable.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Sent when an order is executed at a price different than the initial display price.
struct OrderExecutedWithPriceMessage {

    Nanoseconds nanoseconds;
    OrderId order_id;
    OrderBookId order_book_id;
    Side side;
    ExecutedQuantity executed_quantity;
    MatchId match_id;
    ComboGroupId combo_group_id;
    OwnerParticipantId owner_participant_id;
    CounterpartyParticipantId counterparty_participant_id;
    TradePrice trade_price;
    OccurredAtCross occurred_at_cross;
    Printable printable;

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
