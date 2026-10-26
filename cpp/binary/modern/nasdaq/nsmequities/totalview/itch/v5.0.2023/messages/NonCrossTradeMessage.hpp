#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Trade Messages should be included in NASDAQ time-and-sales displays as well as volume and other market statistics
struct NonCrossTradeMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    BuySellIndicator buy_sell_indicator;
    Shares shares;
    Stock stock;
    Price price;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static NonCrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NonCrossTradeMessage*>(buffer);
    }

    // parse method const
    static const NonCrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NonCrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NonCrossTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NonCrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
