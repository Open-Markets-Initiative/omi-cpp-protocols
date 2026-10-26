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

// Market trade price adjustments are sent resulting from modifications of Open, High, Low, Last and volume statistics due to market operations, prior to the instrument moving to the next session within the trade date, or at the close of instrument
struct OpenHighLowLastTradeAdjustmentMessage {

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
    static constexpr char message_type = 't';

    // parse method
    static OpenHighLowLastTradeAdjustmentMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OpenHighLowLastTradeAdjustmentMessage*>(buffer);
    }

    // parse method const
    static const OpenHighLowLastTradeAdjustmentMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OpenHighLowLastTradeAdjustmentMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OpenHighLowLastTradeAdjustmentMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OpenHighLowLastTradeAdjustmentMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
