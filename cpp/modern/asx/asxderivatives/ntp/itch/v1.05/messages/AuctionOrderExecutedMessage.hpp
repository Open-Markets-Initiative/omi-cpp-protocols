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
#include "../types/OppositeOrderId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is sent when orders are executed in the auction at the open of the market
struct AuctionOrderExecutedMessage {

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
    OppositeOrderId opposite_order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static AuctionOrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionOrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const AuctionOrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionOrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionOrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionOrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
