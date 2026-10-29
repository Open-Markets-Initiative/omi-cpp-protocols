#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Side.hpp"
#include "../types/Price.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Sent when an order is executed
struct OrderExecutedMessage {

    Timestamp timestamp;
    OrderId order_id;
    Quantity quantity;
    ExecutionId execution_id;
    Side side;
    Price price;
    Broker broker;
    ContraBroker contra_broker;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
