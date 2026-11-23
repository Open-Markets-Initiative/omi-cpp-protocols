// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/CopOrder.hpp
#pragma once

#include <cstddef>
#include "../types/BrokerNumber.hpp"
#include "../types/OrderId.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

struct cop_order {

    xmt_quantumfeedlevel2::broker_number broker_number;
    xmt_quantumfeedlevel2::order_id order_id;

    // parse method
    static cop_order* parse(std::byte* buffer) {
        return reinterpret_cast<cop_order*>(buffer);
    }

    // parse method const
    static const cop_order* parse(const std::byte* buffer) {
        return reinterpret_cast<const cop_order*>(buffer);
    }
};

// layout verification
static_assert(offsetof(cop_order, broker_number) == 0, "unexpected offset of cop_order::broker_number");
static_assert(offsetof(cop_order, order_id) == 2, "unexpected offset of cop_order::order_id");
static_assert(sizeof(cop_order) == 10, "unexpected sizeof cop_order");

#pragma pack(pop)
}
