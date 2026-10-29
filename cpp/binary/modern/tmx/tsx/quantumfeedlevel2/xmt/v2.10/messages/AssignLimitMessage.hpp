#pragma once

#include "../types/Symbol.hpp"
#include "../types/CalculatedOpeningPrice.hpp"
#include "../types/OrderSide.hpp"
#include "../structs/CopLimit.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct AssignLimitMessage {

    Symbol symbol;
    CalculatedOpeningPrice calculated_opening_price;
    OrderSide order_side;
    CopLimit cop_limit[15];
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static AssignLimitMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AssignLimitMessage*>(buffer);
    }

    // parse method const
    static const AssignLimitMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AssignLimitMessage*>(buffer);
    }
};

#pragma pack(pop)
}
