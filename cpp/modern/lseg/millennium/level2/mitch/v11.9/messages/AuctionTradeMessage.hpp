#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/Quantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/TradeMatchId.hpp"
#include "../types/AuctionType.hpp"
#include "../bitfields/PtModFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent to report details of an auction
struct AuctionTradeMessage {

    Nanosecond nanosecond;
    Quantity quantity;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    Price price;
    TradeMatchId trade_match_id;
    AuctionType auction_type;
    PtModFlags pt_mod_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x51;

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
