#pragma once

#include "../types/Reserved1.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"
#include "../messages/SnapshotDataMessage.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

#pragma pack(push, 1)

// A displayed order that was removed from the IEX Book
struct OrderDeleteMessage {

    Reserved1 reserved_1;
    Timestamp timestamp;
    Symbol symbol;
    OrderIdReference order_id_reference;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static OrderDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeleteMessage*>(buffer);
    }

    // parse method const
    static const OrderDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeleteMessage* parse(const SnapshotDataMessage* header) {
        return reinterpret_cast<const OrderDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SnapshotDataMessage));
    }
};

#pragma pack(pop)
}
