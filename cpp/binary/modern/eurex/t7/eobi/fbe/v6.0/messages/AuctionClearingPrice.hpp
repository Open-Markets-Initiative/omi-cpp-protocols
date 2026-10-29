#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"
#include "../types/ImbalanceQty.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PotentialSecurityTradingEvent.hpp"
#include "../types/Pad6.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct AuctionClearingPrice {

    TransactTime transact_time;
    SecurityId security_id;
    LastPx last_px;
    LastQty last_qty;
    ImbalanceQty imbalance_qty;
    SecurityTradingStatus security_trading_status;
    PotentialSecurityTradingEvent potential_security_trading_event;
    Pad6 pad6;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13501;

    // parse method
    static AuctionClearingPrice* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionClearingPrice*>(buffer);
    }

    // parse method const
    static const AuctionClearingPrice* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionClearingPrice*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionClearingPrice* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const AuctionClearingPrice*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
