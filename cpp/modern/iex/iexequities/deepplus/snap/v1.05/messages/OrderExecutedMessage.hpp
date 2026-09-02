#pragma once

#include "../bitfields/SaleConditionFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../types/TradeId.hpp"
#include "../messages/SnapshotDataMessage.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

#pragma pack(push, 1)

// A displayed order that was executed against
struct OrderExecutedMessage {

    SaleConditionFlags sale_condition_flags;
    Timestamp timestamp;
    Symbol symbol;
    OrderIdReference order_id_reference;
    Size size;
    Price price;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const SnapshotDataMessage* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SnapshotDataMessage));
    }
};

#pragma pack(pop)
}
