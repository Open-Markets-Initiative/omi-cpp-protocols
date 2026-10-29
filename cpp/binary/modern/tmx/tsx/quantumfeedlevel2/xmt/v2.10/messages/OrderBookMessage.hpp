#pragma once

#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PriorityTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct OrderBookMessage {

    Symbol symbol;
    BrokerNumber broker_number;
    OrderSide order_side;
    OrderId order_id;
    Price price;
    Volume volume;
    PriorityTimeStamp priority_time_stamp;

    // parse method
    static OrderBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookMessage*>(buffer);
    }

    // parse method const
    static const OrderBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookMessage*>(buffer);
    }
};

#pragma pack(pop)
}
