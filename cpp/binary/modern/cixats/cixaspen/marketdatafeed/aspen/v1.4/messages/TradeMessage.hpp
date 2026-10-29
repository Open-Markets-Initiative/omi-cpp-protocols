#pragma once

#include "../types/SymbolId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Symbol.hpp"
#include "../types/Price.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Sent when a hidden order is executed
struct TradeMessage {

    SymbolId symbol_id;
    Timestamp timestamp;
    Reserved8 reserved_8;
    Side side;
    Shares shares;
    Symbol symbol;
    Price price;
    ExecutionId execution_id;
    Broker broker;
    ContraBroker contra_broker;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
