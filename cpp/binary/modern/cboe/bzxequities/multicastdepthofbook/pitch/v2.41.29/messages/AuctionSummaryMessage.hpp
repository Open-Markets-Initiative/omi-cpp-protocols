#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/AuctionOpeningType.hpp"
#include "../types/Price.hpp"
#include "../types/SharesContracts.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// Auction Summary messages are used to disseminate the results of an auction of a complex instrument. An Opening or Re-Opening Auction Summary message for each complex instrument is sent at the conclusion of its Opening or Re-Opening auction and represents Cboe opening price.
struct AuctionSummaryMessage {

    TimeOffset time_offset;
    SymbolLong symbol_long;
    AuctionOpeningType auction_opening_type;
    Price price;
    SharesContracts shares_contracts;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x96;

    // parse method
    static AuctionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionSummaryMessage*>(buffer);
    }

    // parse method const
    static const AuctionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
