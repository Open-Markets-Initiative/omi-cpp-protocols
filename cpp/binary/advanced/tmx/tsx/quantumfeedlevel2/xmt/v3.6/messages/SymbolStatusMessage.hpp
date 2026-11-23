// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/SymbolStatusMessage.hpp
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
#include "../types/ListingMarket.hpp"
#include "../types/ProductType.hpp"
#include "../types/BuyMaximumQuantity.hpp"
#include "../types/BuyMinimumQuantity.hpp"
#include "../types/SellMaximumQuantity.hpp"
#include "../types/SellMinimumQuantity.hpp"
#include "../types/StockState.hpp"
#include "../types/TestSymbol.hpp"
#include "../types/MocEligible.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

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
        xmt_quantumfeedlevel2::listing_market listing_market;
        xmt_quantumfeedlevel2::product_type product_type;
        xmt_quantumfeedlevel2::buy_maximum_quantity buy_maximum_quantity;
        xmt_quantumfeedlevel2::buy_minimum_quantity buy_minimum_quantity;
        xmt_quantumfeedlevel2::sell_maximum_quantity sell_maximum_quantity;
        xmt_quantumfeedlevel2::sell_minimum_quantity sell_minimum_quantity;
        xmt_quantumfeedlevel2::stock_state stock_state;
        xmt_quantumfeedlevel2::test_symbol test_symbol;
        xmt_quantumfeedlevel2::moc_eligible moc_eligible;
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
static_assert(offsetof(symbol_status_message::fields_type, stock_group) == 12, "unexpected offset of symbol_status_message::fields_type::stock_group");
static_assert(offsetof(symbol_status_message::fields_type, cusip) == 13, "unexpected offset of symbol_status_message::fields_type::cusip");
static_assert(offsetof(symbol_status_message::fields_type, board_lot) == 25, "unexpected offset of symbol_status_message::fields_type::board_lot");
static_assert(offsetof(symbol_status_message::fields_type, currency) == 27, "unexpected offset of symbol_status_message::fields_type::currency");
static_assert(offsetof(symbol_status_message::fields_type, face_value) == 28, "unexpected offset of symbol_status_message::fields_type::face_value");
static_assert(offsetof(symbol_status_message::fields_type, last_sale) == 36, "unexpected offset of symbol_status_message::fields_type::last_sale");
static_assert(offsetof(symbol_status_message::fields_type, listing_market) == 44, "unexpected offset of symbol_status_message::fields_type::listing_market");
static_assert(offsetof(symbol_status_message::fields_type, product_type) == 45, "unexpected offset of symbol_status_message::fields_type::product_type");
static_assert(offsetof(symbol_status_message::fields_type, buy_maximum_quantity) == 46, "unexpected offset of symbol_status_message::fields_type::buy_maximum_quantity");
static_assert(offsetof(symbol_status_message::fields_type, buy_minimum_quantity) == 50, "unexpected offset of symbol_status_message::fields_type::buy_minimum_quantity");
static_assert(offsetof(symbol_status_message::fields_type, sell_maximum_quantity) == 54, "unexpected offset of symbol_status_message::fields_type::sell_maximum_quantity");
static_assert(offsetof(symbol_status_message::fields_type, sell_minimum_quantity) == 58, "unexpected offset of symbol_status_message::fields_type::sell_minimum_quantity");
static_assert(offsetof(symbol_status_message::fields_type, stock_state) == 62, "unexpected offset of symbol_status_message::fields_type::stock_state");
static_assert(offsetof(symbol_status_message::fields_type, test_symbol) == 64, "unexpected offset of symbol_status_message::fields_type::test_symbol");
static_assert(offsetof(symbol_status_message::fields_type, moc_eligible) == 65, "unexpected offset of symbol_status_message::fields_type::moc_eligible");
static_assert(sizeof(symbol_status_message::fields_type) == 66, "unexpected sizeof symbol_status_message::fields_type");
static_assert(sizeof(symbol_status_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 66, "unexpected sizeof symbol_status_message");

#pragma pack(pop)
}
