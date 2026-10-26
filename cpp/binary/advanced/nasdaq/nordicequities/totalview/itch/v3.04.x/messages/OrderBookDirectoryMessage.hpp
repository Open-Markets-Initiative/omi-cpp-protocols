#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"
#include "../types/Symbol.hpp"
#include "../types/Isin.hpp"
#include "../types/FinancialProduct.hpp"
#include "../types/TradingCurrency.hpp"
#include "../types/Mic.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/NoteCodesBitField1.hpp"
#include "../types/NoteCodesBitField2.hpp"
#include "../types/NoteCodesBitField3.hpp"
#include "../types/NoteCodesBitField4.hpp"
#include "../types/NoteCodesBitField5.hpp"
#include "../types/NoteCodesBitField6.hpp"
#include "../types/NoteCodesBitField7.hpp"
#include "../types/NoteCodesBitField8.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/NordicMidMic.hpp"
#include "../types/AodMic.hpp"
#include "../types/NotationOfQty.hpp"
#include "../types/NotionalAmount.hpp"
#include "../types/Currency.hpp"
#include "../types/PriceNotation.hpp"
#include "../types/MultiplierForCalculatingQuantityInMeasurementUnit.hpp"
#include "../types/PureStreamMic.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Order Book Directory Message
struct order_book_directory_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_book order_book;
        itch_totalview::symbol symbol;
        itch_totalview::isin isin;
        itch_totalview::financial_product financial_product;
        itch_totalview::trading_currency trading_currency;
        itch_totalview::mic mic;
        itch_totalview::market_segment_id market_segment_id;
        itch_totalview::note_codes_bit_field_1 note_codes_bit_field_1;
        itch_totalview::note_codes_bit_field_2 note_codes_bit_field_2;
        itch_totalview::note_codes_bit_field_3 note_codes_bit_field_3;
        itch_totalview::note_codes_bit_field_4 note_codes_bit_field_4;
        itch_totalview::note_codes_bit_field_5 note_codes_bit_field_5;
        itch_totalview::note_codes_bit_field_6 note_codes_bit_field_6;
        itch_totalview::note_codes_bit_field_7 note_codes_bit_field_7;
        itch_totalview::note_codes_bit_field_8 note_codes_bit_field_8;
        itch_totalview::round_lot_size round_lot_size;
        itch_totalview::nordic_mid_mic nordic_mid_mic;
        itch_totalview::aod_mic aod_mic;
        itch_totalview::notation_of_qty notation_of_qty;
        itch_totalview::notional_amount notional_amount;
        itch_totalview::currency currency;
        itch_totalview::price_notation price_notation;
        itch_totalview::multiplier_for_calculating_quantity_in_measurement_unit multiplier_for_calculating_quantity_in_measurement_unit;
        itch_totalview::pure_stream_mic pure_stream_mic;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_book_directory_message};

    fields_type fields;

    // parse method
    static order_book_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_directory_message*>(buffer);
    }

    // parse method const
    static const order_book_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_directory_message::fields_type, timestamp) == 0, "unexpected offset of order_book_directory_message::fields_type::timestamp");
static_assert(offsetof(order_book_directory_message::fields_type, tracking_number) == 8, "unexpected offset of order_book_directory_message::fields_type::tracking_number");
static_assert(offsetof(order_book_directory_message::fields_type, order_book) == 10, "unexpected offset of order_book_directory_message::fields_type::order_book");
static_assert(offsetof(order_book_directory_message::fields_type, symbol) == 14, "unexpected offset of order_book_directory_message::fields_type::symbol");
static_assert(offsetof(order_book_directory_message::fields_type, isin) == 30, "unexpected offset of order_book_directory_message::fields_type::isin");
static_assert(offsetof(order_book_directory_message::fields_type, financial_product) == 42, "unexpected offset of order_book_directory_message::fields_type::financial_product");
static_assert(offsetof(order_book_directory_message::fields_type, trading_currency) == 43, "unexpected offset of order_book_directory_message::fields_type::trading_currency");
static_assert(offsetof(order_book_directory_message::fields_type, mic) == 46, "unexpected offset of order_book_directory_message::fields_type::mic");
static_assert(offsetof(order_book_directory_message::fields_type, market_segment_id) == 50, "unexpected offset of order_book_directory_message::fields_type::market_segment_id");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_1) == 52, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_1");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_2) == 53, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_2");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_3) == 54, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_3");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_4) == 55, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_4");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_5) == 56, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_5");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_6) == 57, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_6");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_7) == 58, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_7");
static_assert(offsetof(order_book_directory_message::fields_type, note_codes_bit_field_8) == 59, "unexpected offset of order_book_directory_message::fields_type::note_codes_bit_field_8");
static_assert(offsetof(order_book_directory_message::fields_type, round_lot_size) == 60, "unexpected offset of order_book_directory_message::fields_type::round_lot_size");
static_assert(offsetof(order_book_directory_message::fields_type, nordic_mid_mic) == 64, "unexpected offset of order_book_directory_message::fields_type::nordic_mid_mic");
static_assert(offsetof(order_book_directory_message::fields_type, aod_mic) == 68, "unexpected offset of order_book_directory_message::fields_type::aod_mic");
static_assert(offsetof(order_book_directory_message::fields_type, notation_of_qty) == 72, "unexpected offset of order_book_directory_message::fields_type::notation_of_qty");
static_assert(offsetof(order_book_directory_message::fields_type, notional_amount) == 76, "unexpected offset of order_book_directory_message::fields_type::notional_amount");
static_assert(offsetof(order_book_directory_message::fields_type, currency) == 84, "unexpected offset of order_book_directory_message::fields_type::currency");
static_assert(offsetof(order_book_directory_message::fields_type, price_notation) == 87, "unexpected offset of order_book_directory_message::fields_type::price_notation");
static_assert(offsetof(order_book_directory_message::fields_type, multiplier_for_calculating_quantity_in_measurement_unit) == 88, "unexpected offset of order_book_directory_message::fields_type::multiplier_for_calculating_quantity_in_measurement_unit");
static_assert(offsetof(order_book_directory_message::fields_type, pure_stream_mic) == 96, "unexpected offset of order_book_directory_message::fields_type::pure_stream_mic");
static_assert(sizeof(order_book_directory_message::fields_type) == 100, "unexpected sizeof order_book_directory_message::fields_type");
static_assert(sizeof(order_book_directory_message) == sizeof(itch_totalview::message_header) + 100, "unexpected sizeof order_book_directory_message");

#pragma pack(pop)
}
