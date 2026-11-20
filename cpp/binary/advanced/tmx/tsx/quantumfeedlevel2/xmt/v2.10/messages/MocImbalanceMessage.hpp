// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/MocImbalanceMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ImbalanceVolume.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ImbalanceReferencePrice.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

#pragma pack(push, 1)

// Moc Imbalance Message
struct moc_imbalance_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::imbalance_side imbalance_side;
        xmt_quantumfeedlevel2::imbalance_volume imbalance_volume;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
        xmt_quantumfeedlevel2::imbalance_reference_price imbalance_reference_price;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static moc_imbalance_message* parse(std::byte* buffer) {
        return reinterpret_cast<moc_imbalance_message*>(buffer);
    }

    // parse method const
    static const moc_imbalance_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const moc_imbalance_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(moc_imbalance_message::fields_type, symbol) == 0, "unexpected offset of moc_imbalance_message::fields_type::symbol");
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_side) == 9, "unexpected offset of moc_imbalance_message::fields_type::imbalance_side");
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_volume) == 10, "unexpected offset of moc_imbalance_message::fields_type::imbalance_volume");
static_assert(offsetof(moc_imbalance_message::fields_type, trading_system_time_stamp) == 14, "unexpected offset of moc_imbalance_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_reference_price) == 22, "unexpected offset of moc_imbalance_message::fields_type::imbalance_reference_price");
static_assert(sizeof(moc_imbalance_message::fields_type) == 30, "unexpected sizeof moc_imbalance_message::fields_type");
static_assert(sizeof(moc_imbalance_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 30, "unexpected sizeof moc_imbalance_message");

#pragma pack(pop)
}
