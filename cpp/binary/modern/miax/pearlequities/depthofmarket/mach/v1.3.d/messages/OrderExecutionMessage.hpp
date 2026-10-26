#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../bitfields/OrderExecutionFlags.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message format is used when a displayed order on the book executes in whole or in part. The execution is identified by a unique Trade ID that is unique across the exchange for the trading day. Subsequent partial executions of the order would be published with the same Order ID but different Trade ID.
struct OrderExecutionMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    OrderId order_id;
    TradeId trade_id;
    Price price;
    Size size;
    OrderExecutionFlags order_execution_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 24;

    // parse method
    static OrderExecutionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutionMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutionMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const OrderExecutionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
