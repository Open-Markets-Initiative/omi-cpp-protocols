#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/OpeningTrade.hpp"
#include "../types/HighestTrade.hpp"
#include "../types/LowestTrade.hpp"
#include "../types/LastTrade.hpp"
#include "../types/LastVolume.hpp"
#include "../types/TotalTradedVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message disseminates the final settlement price of a future or option contracts order book for the trade date it pertains to
struct MarketSettlementMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    OpeningTrade opening_trade;
    HighestTrade highest_trade;
    LowestTrade lowest_trade;
    LastTrade last_trade;
    LastVolume last_volume;
    TotalTradedVolume total_traded_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static MarketSettlementMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketSettlementMessage*>(buffer);
    }

    // parse method const
    static const MarketSettlementMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketSettlementMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketSettlementMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketSettlementMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
