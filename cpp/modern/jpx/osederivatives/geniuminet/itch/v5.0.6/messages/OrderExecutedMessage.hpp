#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchId.hpp"
#include "../types/ComboGroupId.hpp"
#include "../types/ParticipantIdOwner.hpp"
#include "../types/ParticipantIdCounterparty.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Sent whenever an order on the book is executed in whole or in part.
struct OrderExecutedMessage {

    Nanoseconds nanoseconds;
    OrderId order_id;
    OrderBookId order_book_id;
    Side side;
    ExecutedQuantity executed_quantity;
    MatchId match_id;
    ComboGroupId combo_group_id;
    ParticipantIdOwner participant_id_owner;
    ParticipantIdCounterparty participant_id_counterparty;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
