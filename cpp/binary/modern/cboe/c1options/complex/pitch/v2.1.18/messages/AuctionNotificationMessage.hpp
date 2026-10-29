#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Price.hpp"
#include "../types/Quantity.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/AuctionEndOffset.hpp"
#include "../types/ClientId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// Auction Notification messages are used to disseminate order details of a complex auction.
struct AuctionNotificationMessage {

    TimeOffset time_offset;
    ComplexInstrumentId complex_instrument_id;
    AuctionId auction_id;
    AuctionType auction_type;
    SideIndicator side_indicator;
    Price price;
    Quantity quantity;
    CustomerIndicator customer_indicator;
    ParticipantId participant_id;
    AuctionEndOffset auction_end_offset;
    ClientId client_id;

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
