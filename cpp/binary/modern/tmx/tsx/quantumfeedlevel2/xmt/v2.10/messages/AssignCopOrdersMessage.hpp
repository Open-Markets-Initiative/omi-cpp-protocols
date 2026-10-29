#pragma once

#include "../types/Symbol.hpp"
#include "../types/CalculatedOpeningPrice.hpp"
#include "../types/OrderSide.hpp"
#include "../structs/CopOrder.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct AssignCopOrdersMessage {

    Symbol symbol;
    CalculatedOpeningPrice calculated_opening_price;
    OrderSide order_side;
    CopOrder cop_order[15];
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static AssignCopOrdersMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AssignCopOrdersMessage*>(buffer);
    }

    // parse method const
    static const AssignCopOrdersMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AssignCopOrdersMessage*>(buffer);
    }
};

#pragma pack(pop)
}
