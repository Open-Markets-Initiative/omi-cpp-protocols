#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/Stock.hpp"
#include "../types/TradingState.hpp"
#include "../types/Reserved.hpp"
#include "../types/Reason.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// NASDAQ uses this administrative message to indicate the current trading status of a security to the trading community.
struct StockTradingActionMessage {

    Nanoseconds nanoseconds;
    Stock stock;
    TradingState trading_state;
    Reserved reserved;
    Reason reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static StockTradingActionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockTradingActionMessage*>(buffer);
    }

    // parse method const
    static const StockTradingActionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockTradingActionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StockTradingActionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StockTradingActionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
