#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/MatchId.hpp"
#include "../types/ComboGroupId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/TradePrice.hpp"
#include "../types/OwnerParticipantId.hpp"
#include "../types/CounterpartyParticipantId.hpp"
#include "../types/Printable.hpp"
#include "../types/OccurredAtCross.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Execution details for normal match events involving non-displayable order types or cross trades.
struct TradeMessage {

    Nanoseconds nanoseconds;
    MatchId match_id;
    ComboGroupId combo_group_id;
    Side side;
    Quantity quantity;
    OrderBookId order_book_id;
    TradePrice trade_price;
    OwnerParticipantId owner_participant_id;
    CounterpartyParticipantId counterparty_participant_id;
    Printable printable;
    OccurredAtCross occurred_at_cross;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
