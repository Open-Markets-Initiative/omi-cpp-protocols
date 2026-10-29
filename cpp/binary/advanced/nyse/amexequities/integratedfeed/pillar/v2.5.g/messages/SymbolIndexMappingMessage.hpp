#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ExchangeCode.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/SecurityType.hpp"
#include "../types/LotSize.hpp"
#include "../types/PrevClosePrice.hpp"
#include "../types/PrevCloseVolume.hpp"
#include "../types/PriceResolution.hpp"
#include "../types/RoundLot.hpp"
#include "../types/Mpv.hpp"
#include "../types/UnitOfTrade.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::amexequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Symbol Index Mapping Message
struct symbol_index_mapping_message {

    struct fields_type {
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol symbol;
        pillar_integratedfeed::reserved_1 reserved_1;
        pillar_integratedfeed::market_id market_id;
        pillar_integratedfeed::system_id system_id;
        pillar_integratedfeed::exchange_code exchange_code;
        pillar_integratedfeed::price_scale_code price_scale_code;
        pillar_integratedfeed::security_type security_type;
        pillar_integratedfeed::lot_size lot_size;
        pillar_integratedfeed::prev_close_price prev_close_price;
        pillar_integratedfeed::prev_close_volume prev_close_volume;
        pillar_integratedfeed::price_resolution price_resolution;
        pillar_integratedfeed::round_lot round_lot;
        pillar_integratedfeed::mpv mpv;
        pillar_integratedfeed::unit_of_trade unit_of_trade;
        pillar_integratedfeed::reserved_2 reserved_2;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_index_mapping_message};

    fields_type fields;

    // parse method
    static symbol_index_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_index_mapping_message*>(buffer);
    }

    // parse method const
    static const symbol_index_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_index_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_index_mapping_message::fields_type, symbol_index) == 0, "unexpected offset of symbol_index_mapping_message::fields_type::symbol_index");
static_assert(offsetof(symbol_index_mapping_message::fields_type, symbol) == 4, "unexpected offset of symbol_index_mapping_message::fields_type::symbol");
static_assert(offsetof(symbol_index_mapping_message::fields_type, reserved_1) == 15, "unexpected offset of symbol_index_mapping_message::fields_type::reserved_1");
static_assert(offsetof(symbol_index_mapping_message::fields_type, market_id) == 16, "unexpected offset of symbol_index_mapping_message::fields_type::market_id");
static_assert(offsetof(symbol_index_mapping_message::fields_type, system_id) == 18, "unexpected offset of symbol_index_mapping_message::fields_type::system_id");
static_assert(offsetof(symbol_index_mapping_message::fields_type, exchange_code) == 19, "unexpected offset of symbol_index_mapping_message::fields_type::exchange_code");
static_assert(offsetof(symbol_index_mapping_message::fields_type, price_scale_code) == 20, "unexpected offset of symbol_index_mapping_message::fields_type::price_scale_code");
static_assert(offsetof(symbol_index_mapping_message::fields_type, security_type) == 21, "unexpected offset of symbol_index_mapping_message::fields_type::security_type");
static_assert(offsetof(symbol_index_mapping_message::fields_type, lot_size) == 22, "unexpected offset of symbol_index_mapping_message::fields_type::lot_size");
static_assert(offsetof(symbol_index_mapping_message::fields_type, prev_close_price) == 24, "unexpected offset of symbol_index_mapping_message::fields_type::prev_close_price");
static_assert(offsetof(symbol_index_mapping_message::fields_type, prev_close_volume) == 28, "unexpected offset of symbol_index_mapping_message::fields_type::prev_close_volume");
static_assert(offsetof(symbol_index_mapping_message::fields_type, price_resolution) == 32, "unexpected offset of symbol_index_mapping_message::fields_type::price_resolution");
static_assert(offsetof(symbol_index_mapping_message::fields_type, round_lot) == 33, "unexpected offset of symbol_index_mapping_message::fields_type::round_lot");
static_assert(offsetof(symbol_index_mapping_message::fields_type, mpv) == 34, "unexpected offset of symbol_index_mapping_message::fields_type::mpv");
static_assert(offsetof(symbol_index_mapping_message::fields_type, unit_of_trade) == 36, "unexpected offset of symbol_index_mapping_message::fields_type::unit_of_trade");
static_assert(offsetof(symbol_index_mapping_message::fields_type, reserved_2) == 38, "unexpected offset of symbol_index_mapping_message::fields_type::reserved_2");
static_assert(sizeof(symbol_index_mapping_message::fields_type) == 40, "unexpected sizeof symbol_index_mapping_message::fields_type");
static_assert(sizeof(symbol_index_mapping_message) == sizeof(pillar_integratedfeed::message_header) + 40, "unexpected sizeof symbol_index_mapping_message");

#pragma pack(pop)
}
