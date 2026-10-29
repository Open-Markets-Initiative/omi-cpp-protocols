#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongPrice.hpp"
#include "../types/Contracts.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/AuctionEndOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// Auction Notification messages are used to disseminate order details of an auction.
struct AuctionNotificationMessage {

    TimeOffset time_offset;
    Symbol symbol;
    AuctionId auction_id;
    AuctionType auction_type;
    SideIndicator side_indicator;
    LongPrice long_price;
    Contracts contracts;
    CustomerIndicator customer_indicator;
    ParticipantId participant_id;
    AuctionEndOffset auction_end_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xAD;

    // parse method
    static AuctionNotificationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionNotificationMessage*>(buffer);
    }

    // parse method const
    static const AuctionNotificationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionNotificationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionNotificationMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionNotificationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
