#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Carries the best bid and offer of a non crossed order book during an auction call phase.
struct AuctionBestBidOfferMessage {

    TransactTime transact_time;
    SecurityId security_id;
    BidPx bid_px;
    OfferPx offer_px;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13500;

    // parse method
    static AuctionBestBidOfferMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionBestBidOfferMessage*>(buffer);
    }

    // parse method const
    static const AuctionBestBidOfferMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionBestBidOfferMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionBestBidOfferMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionBestBidOfferMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
