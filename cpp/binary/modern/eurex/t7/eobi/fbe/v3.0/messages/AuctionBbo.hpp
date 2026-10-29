#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

// 
struct AuctionBbo {

    TransactTime transact_time;
    SecurityId security_id;
    BidPx bid_px;
    OfferPx offer_px;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13500;

    // parse method
    static AuctionBbo* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionBbo*>(buffer);
    }

    // parse method const
    static const AuctionBbo* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionBbo*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionBbo* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const AuctionBbo*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
