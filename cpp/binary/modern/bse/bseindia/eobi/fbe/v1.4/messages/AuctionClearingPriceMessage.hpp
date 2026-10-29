#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published for a crossed order book in an auction, indicating the potential auction price.
struct AuctionClearingPriceMessage {

    TransactTime transact_time;
    SecurityId security_id;
    LastPx last_px;
    LastQty last_qty;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13501;

    // parse method
    static AuctionClearingPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionClearingPriceMessage*>(buffer);
    }

    // parse method const
    static const AuctionClearingPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionClearingPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionClearingPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionClearingPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
