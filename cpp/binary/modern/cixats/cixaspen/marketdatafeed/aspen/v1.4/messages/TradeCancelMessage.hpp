#pragma once

#include "../types/SymbolId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Shares.hpp"
#include "../types/Symbol.hpp"
#include "../types/Price.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Sent whenever an execution on CIX ATS is cancelled
struct TradeCancelMessage {

    SymbolId symbol_id;
    Timestamp timestamp;
    Reserved8 reserved_8;
    Reserved1 reserved_1;
    Shares shares;
    Symbol symbol;
    Price price;
    ExecutionId execution_id;
    Broker broker;
    ContraBroker contra_broker;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static TradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
