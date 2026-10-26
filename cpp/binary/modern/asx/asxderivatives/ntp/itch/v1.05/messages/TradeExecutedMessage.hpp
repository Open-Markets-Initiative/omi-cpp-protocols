#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/TradeType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/TradePrice.hpp"
#include "../types/CombinationTradeId.hpp"
#include "../types/ParticipantIdBuyer.hpp"
#include "../types/ParticipantIdSeller.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// The Trade Message is designed to provide details for executions in combination order books. Trade Executed messages are reported in the same sequence as order execution messages are reported
struct TradeExecutedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    TradeType trade_type;
    TradeId trade_id;
    ExecutedQuantity executed_quantity;
    TradePrice trade_price;
    CombinationTradeId combination_trade_id;
    ParticipantIdBuyer participant_id_buyer;
    ParticipantIdSeller participant_id_seller;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static TradeExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeExecutedMessage*>(buffer);
    }

    // parse method const
    static const TradeExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
