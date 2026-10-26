#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/AuctionId.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/PriceLong.hpp"
#include "../types/Contracts.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// C1 and EDGX Options Only. Auction Trade messages are used to disseminate executions resulting from an options auction.
struct AuctionTradeMessage {

    TimeOffset time_offset;
    AuctionId auction_id;
    ExecutionId execution_id;
    PriceLong price_long;
    Contracts contracts;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xAF;

    // parse method
    static AuctionTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionTradeMessage*>(buffer);
    }

    // parse method const
    static const AuctionTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
