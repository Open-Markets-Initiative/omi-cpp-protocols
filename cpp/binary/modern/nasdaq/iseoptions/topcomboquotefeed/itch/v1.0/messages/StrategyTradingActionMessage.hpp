#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/CurrentTradingState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

// ISE uses this administrative message to indicate the current trading status of a strategy within the ISE Options Market.
struct StrategyTradingActionMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    CurrentTradingState current_trading_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static StrategyTradingActionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StrategyTradingActionMessage*>(buffer);
    }

    // parse method const
    static const StrategyTradingActionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrategyTradingActionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StrategyTradingActionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StrategyTradingActionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
