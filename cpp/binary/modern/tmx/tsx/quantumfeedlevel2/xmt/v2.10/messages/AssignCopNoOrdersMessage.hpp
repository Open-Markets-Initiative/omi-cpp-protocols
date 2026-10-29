#pragma once

#include "../types/Symbol.hpp"
#include "../types/CalculatedOpeningPrice.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct AssignCopNoOrdersMessage {

    Symbol symbol;
    CalculatedOpeningPrice calculated_opening_price;
    TradingSystemTimeStamp trading_system_time_stamp;

    // parse method
    static AssignCopNoOrdersMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AssignCopNoOrdersMessage*>(buffer);
    }

    // parse method const
    static const AssignCopNoOrdersMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AssignCopNoOrdersMessage*>(buffer);
    }
};

#pragma pack(pop)
}
