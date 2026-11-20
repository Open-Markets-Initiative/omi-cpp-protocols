// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/CopLimit.hpp
#pragma once

#include <cstddef>
#include "../types/BrokerNumber.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

#pragma pack(push, 1)

struct cop_limit {

    xmt_quantumfeedlevel2::broker_number broker_number;
    xmt_quantumfeedlevel2::order_id order_id;
    xmt_quantumfeedlevel2::price price;

    // parse method
    static cop_limit* parse(std::byte* buffer) {
        return reinterpret_cast<cop_limit*>(buffer);
    }

    // parse method const
    static const cop_limit* parse(const std::byte* buffer) {
        return reinterpret_cast<const cop_limit*>(buffer);
    }
};

// layout verification
static_assert(offsetof(cop_limit, broker_number) == 0, "unexpected offset of cop_limit::broker_number");
static_assert(offsetof(cop_limit, order_id) == 2, "unexpected offset of cop_limit::order_id");
static_assert(offsetof(cop_limit, price) == 10, "unexpected offset of cop_limit::price");
static_assert(sizeof(cop_limit) == 18, "unexpected sizeof cop_limit");

#pragma pack(pop)
}
