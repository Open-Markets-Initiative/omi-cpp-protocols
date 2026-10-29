#pragma once

#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/NonResident.hpp"
#include "../types/SettlementTerms.hpp"
#include "../types/SettlementDate.hpp"
#include "../types/PriorityTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

// 
struct OrderBookTermsMessage {

    Symbol symbol;
    BrokerNumber broker_number;
    OrderSide order_side;
    OrderId order_id;
    Price price;
    Volume volume;
    NonResident non_resident;
    SettlementTerms settlement_terms;
    SettlementDate settlement_date;
    PriorityTimeStamp priority_time_stamp;

    // parse method
    static OrderBookTermsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookTermsMessage*>(buffer);
    }

    // parse method const
    static const OrderBookTermsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookTermsMessage*>(buffer);
    }
};

#pragma pack(pop)
}
