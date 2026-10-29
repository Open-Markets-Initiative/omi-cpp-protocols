#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// The Trade Message is designed to provide execution details for normal match events involving non-displayable order types.
struct TradeMessage {

    Nanoseconds nanoseconds;
    OrderReferenceNumber order_reference_number;
    Side side;
    Shares shares;
    Stock stock;
    Price price;
    MatchNumber match_number;

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
