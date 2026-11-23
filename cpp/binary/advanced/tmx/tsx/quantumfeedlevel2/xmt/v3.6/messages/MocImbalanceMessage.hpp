// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MocImbalanceMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ImbalanceVolume.hpp"
#include "../types/TradingSystemTimeStamp.hpp"
#include "../types/ImbalanceReferencePrice.hpp"
#include "../types/PairedVolume.hpp"
#include "../types/MarketOrderImbalanceVolume.hpp"
#include "../types/MarketOrderImbalanceSide.hpp"
#include "../types/NearIndicativeClosingPrice.hpp"
#include "../types/FarIndicativeClosingPrice.hpp"
#include "../types/PriceVariation.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Moc Imbalance Message
struct moc_imbalance_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::imbalance_side imbalance_side;
        xmt_quantumfeedlevel2::imbalance_volume imbalance_volume;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
        xmt_quantumfeedlevel2::imbalance_reference_price imbalance_reference_price;
        xmt_quantumfeedlevel2::paired_volume paired_volume;
        xmt_quantumfeedlevel2::market_order_imbalance_volume market_order_imbalance_volume;
        xmt_quantumfeedlevel2::market_order_imbalance_side market_order_imbalance_side;
        xmt_quantumfeedlevel2::near_indicative_closing_price near_indicative_closing_price;
        xmt_quantumfeedlevel2::far_indicative_closing_price far_indicative_closing_price;
        xmt_quantumfeedlevel2::price_variation price_variation;
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
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_side) == 12, "unexpected offset of moc_imbalance_message::fields_type::imbalance_side");
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_volume) == 13, "unexpected offset of moc_imbalance_message::fields_type::imbalance_volume");
static_assert(offsetof(moc_imbalance_message::fields_type, trading_system_time_stamp) == 17, "unexpected offset of moc_imbalance_message::fields_type::trading_system_time_stamp");
static_assert(offsetof(moc_imbalance_message::fields_type, imbalance_reference_price) == 25, "unexpected offset of moc_imbalance_message::fields_type::imbalance_reference_price");
static_assert(offsetof(moc_imbalance_message::fields_type, paired_volume) == 33, "unexpected offset of moc_imbalance_message::fields_type::paired_volume");
static_assert(offsetof(moc_imbalance_message::fields_type, market_order_imbalance_volume) == 37, "unexpected offset of moc_imbalance_message::fields_type::market_order_imbalance_volume");
static_assert(offsetof(moc_imbalance_message::fields_type, market_order_imbalance_side) == 41, "unexpected offset of moc_imbalance_message::fields_type::market_order_imbalance_side");
static_assert(offsetof(moc_imbalance_message::fields_type, near_indicative_closing_price) == 42, "unexpected offset of moc_imbalance_message::fields_type::near_indicative_closing_price");
static_assert(offsetof(moc_imbalance_message::fields_type, far_indicative_closing_price) == 50, "unexpected offset of moc_imbalance_message::fields_type::far_indicative_closing_price");
static_assert(offsetof(moc_imbalance_message::fields_type, price_variation) == 58, "unexpected offset of moc_imbalance_message::fields_type::price_variation");
static_assert(sizeof(moc_imbalance_message::fields_type) == 62, "unexpected sizeof moc_imbalance_message::fields_type");
static_assert(sizeof(moc_imbalance_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 62, "unexpected sizeof moc_imbalance_message");

#pragma pack(pop)
}
