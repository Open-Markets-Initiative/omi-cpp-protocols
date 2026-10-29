#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/AuctionId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// Auction Cancel messages are used to disseminate the cancelation of an earlier Auction Notification message as a result of a user cancelation of the original complex auction, a user modification request to change the complex auction price or increase the original complex auction quantity, a fading of the NBBO or to cancel any remaining complex auction quantity from the original Auction Notification following the complex auction termination.
struct AuctionCancelMessage {

    TimeOffset time_offset;
    AuctionId auction_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xAE;

    // parse method
    static AuctionCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionCancelMessage*>(buffer);
    }

    // parse method const
    static const AuctionCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
