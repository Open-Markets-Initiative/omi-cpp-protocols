#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../types/BidSize.hpp"
#include "../types/OfferSize.hpp"
#include "../types/PotentialSecurityTradingEvent.hpp"
#include "../types/BidOrdType.hpp"
#include "../types/OfferOrdType.hpp"
#include "../types/Pad5.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct AuctionBbo {

    TransactTime transact_time;
    SecurityId security_id;
    BidPx bid_px;
    OfferPx offer_px;
    BidSize bid_size;
    OfferSize offer_size;
    PotentialSecurityTradingEvent potential_security_trading_event;
    BidOrdType bid_ord_type;
    OfferOrdType offer_ord_type;
    Pad5 pad5;

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
