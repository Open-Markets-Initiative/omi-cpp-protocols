#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/TradeType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/TradePrice.hpp"
#include "../types/BuyerTradeableInstrumentId.hpp"
#include "../types/BuyerSide.hpp"
#include "../types/BuyerOrderId.hpp"
#include "../types/BuyerCombinationTradeId.hpp"
#include "../types/BuyerParticipantId.hpp"
#include "../types/SellerTradeableInstrumentId.hpp"
#include "../types/SellerSide.hpp"
#include "../types/SellerOrderId.hpp"
#include "../types/SellerCombinationTradeId.hpp"
#include "../types/SellerParticipantId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// The Combination Trade Executed Message is designed to provide details for executions where one or both orders are resting from a different order book id from the order book id of the trade
struct CombinationTradeExecutedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    TradeType trade_type;
    TradeId trade_id;
    ExecutedQuantity executed_quantity;
    TradePrice trade_price;
    BuyerTradeableInstrumentId buyer_tradeable_instrument_id;
    BuyerSide buyer_side;
    BuyerOrderId buyer_order_id;
    BuyerCombinationTradeId buyer_combination_trade_id;
    BuyerParticipantId buyer_participant_id;
    SellerTradeableInstrumentId seller_tradeable_instrument_id;
    SellerSide seller_side;
    SellerOrderId seller_order_id;
    SellerCombinationTradeId seller_combination_trade_id;
    SellerParticipantId seller_participant_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'p';

    // parse method
    static CombinationTradeExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CombinationTradeExecutedMessage*>(buffer);
    }

    // parse method const
    static const CombinationTradeExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CombinationTradeExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CombinationTradeExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CombinationTradeExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
