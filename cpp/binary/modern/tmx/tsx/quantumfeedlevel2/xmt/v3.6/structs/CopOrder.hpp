// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/CopOrder.hpp
#pragma once

#include "../types/BrokerNumber.hpp"
#include "../types/OrderId.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

#pragma pack(push, 1)

struct CopOrder {

    BrokerNumber broker_number;
    OrderId order_id;

    // parse method
    static CopOrder* parse(std::byte* buffer) {
        return reinterpret_cast<CopOrder*>(buffer);
    }

    // parse method const
    static const CopOrder* parse(const std::byte* buffer) {
        return reinterpret_cast<const CopOrder*>(buffer);
    }
};

#pragma pack(pop)
}
