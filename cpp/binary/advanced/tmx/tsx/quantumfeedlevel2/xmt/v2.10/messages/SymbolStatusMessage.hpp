// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/SymbolStatusMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/StockGroup.hpp"
#include "../types/Cusip.hpp"
#include "../types/BoardLot.hpp"
#include "../types/Currency.hpp"
#include "../types/FaceValue.hpp"
#include "../types/LastSale.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

#pragma pack(push, 1)

// Symbol Status Message
struct symbol_status_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::stock_group stock_group;
        xmt_quantumfeedlevel2::cusip cusip;
        xmt_quantumfeedlevel2::board_lot board_lot;
        xmt_quantumfeedlevel2::currency currency;
        xmt_quantumfeedlevel2::face_value face_value;
        xmt_quantumfeedlevel2::last_sale last_sale;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static symbol_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_status_message*>(buffer);
    }

    // parse method const
    static const symbol_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_status_message::fields_type, symbol) == 0, "unexpected offset of symbol_status_message::fields_type::symbol");
static_assert(offsetof(symbol_status_message::fields_type, stock_group) == 9, "unexpected offset of symbol_status_message::fields_type::stock_group");
static_assert(offsetof(symbol_status_message::fields_type, cusip) == 10, "unexpected offset of symbol_status_message::fields_type::cusip");
static_assert(offsetof(symbol_status_message::fields_type, board_lot) == 22, "unexpected offset of symbol_status_message::fields_type::board_lot");
static_assert(offsetof(symbol_status_message::fields_type, currency) == 24, "unexpected offset of symbol_status_message::fields_type::currency");
static_assert(offsetof(symbol_status_message::fields_type, face_value) == 25, "unexpected offset of symbol_status_message::fields_type::face_value");
static_assert(offsetof(symbol_status_message::fields_type, last_sale) == 33, "unexpected offset of symbol_status_message::fields_type::last_sale");
static_assert(sizeof(symbol_status_message::fields_type) == 41, "unexpected sizeof symbol_status_message::fields_type");
static_assert(sizeof(symbol_status_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 41, "unexpected sizeof symbol_status_message");

#pragma pack(pop)
}
