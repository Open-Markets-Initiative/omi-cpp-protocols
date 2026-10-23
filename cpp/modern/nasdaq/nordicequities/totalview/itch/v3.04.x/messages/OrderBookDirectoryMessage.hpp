#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"
#include "../types/Symbol.hpp"
#include "../types/Isin.hpp"
#include "../types/FinancialProduct.hpp"
#include "../types/TradingCurrency.hpp"
#include "../types/Mic.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../bitfields/NoteCodesBitField1.hpp"
#include "../bitfields/NoteCodesBitField2.hpp"
#include "../bitfields/NoteCodesBitField3.hpp"
#include "../bitfields/NoteCodesBitField4.hpp"
#include "../bitfields/NoteCodesBitField5.hpp"
#include "../bitfields/NoteCodesBitField6.hpp"
#include "../bitfields/NoteCodesBitField7.hpp"
#include "../bitfields/NoteCodesBitField8.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/NordicMidMic.hpp"
#include "../types/AodMic.hpp"
#include "../types/NotationOfQty.hpp"
#include "../types/NotionalAmount.hpp"
#include "../types/Currency.hpp"
#include "../types/PriceNotation.hpp"
#include "../types/MultiplierForCalculatingQuantityInMeasurementUnit.hpp"
#include "../types/PureStreamMic.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Disseminated for all active order books at the start of each trading day
struct OrderBookDirectoryMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderBook order_book;
    Symbol symbol;
    Isin isin;
    FinancialProduct financial_product;
    TradingCurrency trading_currency;
    Mic mic;
    MarketSegmentId market_segment_id;
    NoteCodesBitField1 note_codes_bit_field_1;
    NoteCodesBitField2 note_codes_bit_field_2;
    NoteCodesBitField3 note_codes_bit_field_3;
    NoteCodesBitField4 note_codes_bit_field_4;
    NoteCodesBitField5 note_codes_bit_field_5;
    NoteCodesBitField6 note_codes_bit_field_6;
    NoteCodesBitField7 note_codes_bit_field_7;
    NoteCodesBitField8 note_codes_bit_field_8;
    RoundLotSize round_lot_size;
    NordicMidMic nordic_mid_mic;
    AodMic aod_mic;
    NotationOfQty notation_of_qty;
    NotionalAmount notional_amount;
    Currency currency;
    PriceNotation price_notation;
    MultiplierForCalculatingQuantityInMeasurementUnit multiplier_for_calculating_quantity_in_measurement_unit;
    PureStreamMic pure_stream_mic;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static OrderBookDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookDirectoryMessage*>(buffer);
    }

    // parse method const
    static const OrderBookDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
