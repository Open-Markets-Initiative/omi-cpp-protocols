#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/AuctionCollarReferencePrice.hpp"
#include "../types/UpperAuctionCollarPrice.hpp"
#include "../types/LowerAuctionCollarPrice.hpp"
#include "../types/AuctionCollarExtension.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Indicates the auction collar thresholds within which a paused security can reopen following a LULD trading pause
struct LuldAuctionCollarMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    AuctionCollarReferencePrice auction_collar_reference_price;
    UpperAuctionCollarPrice upper_auction_collar_price;
    LowerAuctionCollarPrice lower_auction_collar_price;
    AuctionCollarExtension auction_collar_extension;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static LuldAuctionCollarMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LuldAuctionCollarMessage*>(buffer);
    }

    // parse method const
    static const LuldAuctionCollarMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LuldAuctionCollarMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LuldAuctionCollarMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LuldAuctionCollarMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
