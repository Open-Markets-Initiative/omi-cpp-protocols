#pragma once

#include "../types/SymbolId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Symbol.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/OriginalExecutionId.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeQuantity.hpp"
#include "../types/CorrectedTradePrice.hpp"
#include "../types/CorrectedTradeQuantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Sent whenever an execution on CIX ATS is amended
struct TradeCorrectMessage {

    SymbolId symbol_id;
    Timestamp timestamp;
    Reserved8 reserved_8;
    Reserved1 reserved_1;
    Symbol symbol;
    ExecutionId execution_id;
    Broker broker;
    ContraBroker contra_broker;
    OriginalExecutionId original_execution_id;
    OriginalTradePrice original_trade_price;
    OriginalTradeQuantity original_trade_quantity;
    CorrectedTradePrice corrected_trade_price;
    CorrectedTradeQuantity corrected_trade_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

    // parse method
    static TradeCorrectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCorrectMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCorrectMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
