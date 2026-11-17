// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/MarketDataRefreshMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PriceType.hpp"
#include "../types/ApplSeqNum.hpp"
#include "../structs/PrevClosePx.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// The Market Data Refresh message contains a snapshot / refresh of the Current Market and Recap information (Last Sale, Last Sale Size, Open, High, Low, Previous Close Price) for one product.
struct MarketDataRefreshMessage {

    ClassKey class_key;
    SecurityId security_id;
    SecurityTradingStatus security_trading_status;
    PriceType price_type;
    ApplSeqNum appl_seq_num;
    PrevClosePx prev_close_px;
    TradeVolume trade_volume;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 20;

    // parse method
    static MarketDataRefreshMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketDataRefreshMessage*>(buffer);
    }

    // parse method const
    static const MarketDataRefreshMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketDataRefreshMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketDataRefreshMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketDataRefreshMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
