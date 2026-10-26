#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Symbol.hpp"
#include "../types/LongName.hpp"
#include "../types/Isin.hpp"
#include "../types/FinancialProduct.hpp"
#include "../types/TradingCurrency.hpp"
#include "../types/DecimalsInPrice.hpp"
#include "../types/DecimalsInNominalValue.hpp"
#include "../types/OddLotSize.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/BlockLotSize.hpp"
#include "../types/NominalValue.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../types/UnderlyingOrderbookId.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/DecimalsInStrikePrice.hpp"
#include "../types/PutOrCall.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Order Book Directory
struct order_book_directory {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::symbol symbol;
        itch_geniuminet::long_name long_name;
        itch_geniuminet::isin isin;
        itch_geniuminet::financial_product financial_product;
        itch_geniuminet::trading_currency trading_currency;
        itch_geniuminet::decimals_in_price decimals_in_price;
        itch_geniuminet::decimals_in_nominal_value decimals_in_nominal_value;
        itch_geniuminet::odd_lot_size odd_lot_size;
        itch_geniuminet::round_lot_size round_lot_size;
        itch_geniuminet::block_lot_size block_lot_size;
        itch_geniuminet::nominal_value nominal_value;
        itch_geniuminet::number_of_legs number_of_legs;
        itch_geniuminet::underlying_orderbook_id underlying_orderbook_id;
        itch_geniuminet::strike_price strike_price;
        itch_geniuminet::expiration_date expiration_date;
        itch_geniuminet::decimals_in_strike_price decimals_in_strike_price;
        itch_geniuminet::put_or_call put_or_call;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_book_directory};

    fields_type fields;

    // parse method
    static order_book_directory* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_directory*>(buffer);
    }

    // parse method const
    static const order_book_directory* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_directory*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_directory::fields_type, nanoseconds) == 0, "unexpected offset of order_book_directory::fields_type::nanoseconds");
static_assert(offsetof(order_book_directory::fields_type, order_book_id) == 4, "unexpected offset of order_book_directory::fields_type::order_book_id");
static_assert(offsetof(order_book_directory::fields_type, symbol) == 8, "unexpected offset of order_book_directory::fields_type::symbol");
static_assert(offsetof(order_book_directory::fields_type, long_name) == 40, "unexpected offset of order_book_directory::fields_type::long_name");
static_assert(offsetof(order_book_directory::fields_type, isin) == 72, "unexpected offset of order_book_directory::fields_type::isin");
static_assert(offsetof(order_book_directory::fields_type, financial_product) == 84, "unexpected offset of order_book_directory::fields_type::financial_product");
static_assert(offsetof(order_book_directory::fields_type, trading_currency) == 85, "unexpected offset of order_book_directory::fields_type::trading_currency");
static_assert(offsetof(order_book_directory::fields_type, decimals_in_price) == 88, "unexpected offset of order_book_directory::fields_type::decimals_in_price");
static_assert(offsetof(order_book_directory::fields_type, decimals_in_nominal_value) == 90, "unexpected offset of order_book_directory::fields_type::decimals_in_nominal_value");
static_assert(offsetof(order_book_directory::fields_type, odd_lot_size) == 92, "unexpected offset of order_book_directory::fields_type::odd_lot_size");
static_assert(offsetof(order_book_directory::fields_type, round_lot_size) == 96, "unexpected offset of order_book_directory::fields_type::round_lot_size");
static_assert(offsetof(order_book_directory::fields_type, block_lot_size) == 100, "unexpected offset of order_book_directory::fields_type::block_lot_size");
static_assert(offsetof(order_book_directory::fields_type, nominal_value) == 104, "unexpected offset of order_book_directory::fields_type::nominal_value");
static_assert(offsetof(order_book_directory::fields_type, number_of_legs) == 112, "unexpected offset of order_book_directory::fields_type::number_of_legs");
static_assert(offsetof(order_book_directory::fields_type, underlying_orderbook_id) == 113, "unexpected offset of order_book_directory::fields_type::underlying_orderbook_id");
static_assert(offsetof(order_book_directory::fields_type, strike_price) == 117, "unexpected offset of order_book_directory::fields_type::strike_price");
static_assert(offsetof(order_book_directory::fields_type, expiration_date) == 121, "unexpected offset of order_book_directory::fields_type::expiration_date");
static_assert(offsetof(order_book_directory::fields_type, decimals_in_strike_price) == 125, "unexpected offset of order_book_directory::fields_type::decimals_in_strike_price");
static_assert(offsetof(order_book_directory::fields_type, put_or_call) == 127, "unexpected offset of order_book_directory::fields_type::put_or_call");
static_assert(sizeof(order_book_directory::fields_type) == 128, "unexpected sizeof order_book_directory::fields_type");
static_assert(sizeof(order_book_directory) == sizeof(itch_geniuminet::message_header) + 128, "unexpected sizeof order_book_directory");

#pragma pack(pop)
}
