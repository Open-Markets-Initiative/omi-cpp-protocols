#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/Price.hpp"
#include "../types/Broker.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// A new resting order added to the book
struct NewOrderAddMessage {

    Timestamp timestamp;
    SymbolId symbol_id;
    OrderId order_id;
    Side side;
    Quantity quantity;
    Symbol symbol;
    Price price;
    Broker broker;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static NewOrderAddMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NewOrderAddMessage*>(buffer);
    }

    // parse method const
    static const NewOrderAddMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NewOrderAddMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NewOrderAddMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NewOrderAddMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
