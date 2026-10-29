#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/TradeId.hpp"
#include "../types/NetPrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Reserved16.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate Trades that are resulting from executions on MIAX during the current trading session
struct StrategyTradeMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    TradeId trade_id;
    NetPrice net_price;
    TradeSize trade_size;
    TradeCondition trade_condition;
    Reserved16 reserved_16;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 't';

    // parse method
    static StrategyTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StrategyTradeMessage*>(buffer);
    }

    // parse method const
    static const StrategyTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrategyTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StrategyTradeMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const StrategyTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
