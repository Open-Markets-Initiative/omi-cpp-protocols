#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityRemaining.hpp"
#include "../types/TradeType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/TradePrice.hpp"
#include "../types/OppositeTradeableInstrumentId.hpp"
#include "../types/OppositeSide.hpp"
#include "../types/OppositeOrderId.hpp"
#include "../types/CombinationTradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is sent whenever a resting order is matched with an open leg of a resting combination order in whole or in part
struct CombinationOrderExecutedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;
    QuantityRemaining quantity_remaining;
    TradeType trade_type;
    TradeId trade_id;
    ExecutedQuantity executed_quantity;
    TradePrice trade_price;
    OppositeTradeableInstrumentId opposite_tradeable_instrument_id;
    OppositeSide opposite_side;
    OppositeOrderId opposite_order_id;
    CombinationTradeId combination_trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'e';

    // parse method
    static CombinationOrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CombinationOrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const CombinationOrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CombinationOrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CombinationOrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CombinationOrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
