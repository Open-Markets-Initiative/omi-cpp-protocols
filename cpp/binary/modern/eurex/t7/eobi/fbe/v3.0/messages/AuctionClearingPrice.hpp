#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

// 
struct AuctionClearingPrice {

    TransactTime transact_time;
    SecurityId security_id;
    LastPx last_px;

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
