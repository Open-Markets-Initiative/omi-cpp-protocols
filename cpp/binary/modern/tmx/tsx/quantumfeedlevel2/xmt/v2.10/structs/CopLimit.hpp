#pragma once

#include "../types/BrokerNumber.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

struct CopLimit {

    BrokerNumber broker_number;
    OrderId order_id;
    Price price;

    // parse method
    static CopLimit* parse(std::byte* buffer) {
        return reinterpret_cast<CopLimit*>(buffer);
    }

    // parse method const
    static const CopLimit* parse(const std::byte* buffer) {
        return reinterpret_cast<const CopLimit*>(buffer);
    }
};

#pragma pack(pop)
}
