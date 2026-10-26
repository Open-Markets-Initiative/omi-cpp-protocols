#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SymbolName.hpp"
#include "../types/LongName.hpp"
#include "../types/Isin.hpp"
#include "../types/Exchange.hpp"
#include "../types/Instrument.hpp"
#include "../types/CfiCode.hpp"
#include "../types/ExpiryYear.hpp"
#include "../types/ExpiryMonth.hpp"
#include "../types/OptionType.hpp"
#include "../types/Strike.hpp"
#include "../types/UnderlyingTradeableInstrumentId.hpp"
#include "../types/PriceDisplayDecimals.hpp"
#include "../types/PriceFractionalDenominator.hpp"
#include "../types/PriceMinimumTick.hpp"
#include "../types/StrikePriceDecimalPosition.hpp"
#include "../types/StrikePriceFractionalDenominator.hpp"
#include "../types/StrikePriceMinimumTick.hpp"
#include "../types/LastTradingDate.hpp"
#include "../types/PriorDaySettlement.hpp"
#include "../types/Volatility.hpp"
#include "../types/Currency.hpp"
#include "../types/LotSizeOrFaceValue.hpp"
#include "../types/MaturityValue.hpp"
#include "../types/CouponRate.hpp"
#include "../types/PaymentsPerYear.hpp"
#include "../types/BlockLotSize.hpp"
#include "../types/ExpiryDate.hpp"
#include "../types/BasisOfQuotation.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Options Symbol Directory Message
struct options_symbol_directory_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::symbol_name symbol_name;
        itch_ntp::long_name long_name;
        itch_ntp::isin isin;
        itch_ntp::exchange exchange;
        itch_ntp::instrument instrument;
        itch_ntp::cfi_code cfi_code;
        itch_ntp::expiry_year expiry_year;
        itch_ntp::expiry_month expiry_month;
        itch_ntp::option_type option_type;
        itch_ntp::strike strike;
        itch_ntp::underlying_tradeable_instrument_id underlying_tradeable_instrument_id;
        itch_ntp::price_display_decimals price_display_decimals;
        itch_ntp::price_fractional_denominator price_fractional_denominator;
        itch_ntp::price_minimum_tick price_minimum_tick;
        itch_ntp::strike_price_decimal_position strike_price_decimal_position;
        itch_ntp::strike_price_fractional_denominator strike_price_fractional_denominator;
        itch_ntp::strike_price_minimum_tick strike_price_minimum_tick;
        itch_ntp::last_trading_date last_trading_date;
        itch_ntp::prior_day_settlement prior_day_settlement;
        itch_ntp::volatility volatility;
        itch_ntp::currency currency;
        itch_ntp::lot_size_or_face_value lot_size_or_face_value;
        itch_ntp::maturity_value maturity_value;
        itch_ntp::coupon_rate coupon_rate;
        itch_ntp::payments_per_year payments_per_year;
        itch_ntp::block_lot_size block_lot_size;
        itch_ntp::expiry_date expiry_date;
        itch_ntp::basis_of_quotation basis_of_quotation;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::options_symbol_directory_message};

    fields_type fields;

    // parse method
    static options_symbol_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_symbol_directory_message*>(buffer);
    }

    // parse method const
    static const options_symbol_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_symbol_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_symbol_directory_message::fields_type, nanoseconds) == 0, "unexpected offset of options_symbol_directory_message::fields_type::nanoseconds");
static_assert(offsetof(options_symbol_directory_message::fields_type, trade_date) == 4, "unexpected offset of options_symbol_directory_message::fields_type::trade_date");
static_assert(offsetof(options_symbol_directory_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of options_symbol_directory_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(options_symbol_directory_message::fields_type, symbol_name) == 10, "unexpected offset of options_symbol_directory_message::fields_type::symbol_name");
static_assert(offsetof(options_symbol_directory_message::fields_type, long_name) == 42, "unexpected offset of options_symbol_directory_message::fields_type::long_name");
static_assert(offsetof(options_symbol_directory_message::fields_type, isin) == 102, "unexpected offset of options_symbol_directory_message::fields_type::isin");
static_assert(offsetof(options_symbol_directory_message::fields_type, exchange) == 114, "unexpected offset of options_symbol_directory_message::fields_type::exchange");
static_assert(offsetof(options_symbol_directory_message::fields_type, instrument) == 120, "unexpected offset of options_symbol_directory_message::fields_type::instrument");
static_assert(offsetof(options_symbol_directory_message::fields_type, cfi_code) == 126, "unexpected offset of options_symbol_directory_message::fields_type::cfi_code");
static_assert(offsetof(options_symbol_directory_message::fields_type, expiry_year) == 132, "unexpected offset of options_symbol_directory_message::fields_type::expiry_year");
static_assert(offsetof(options_symbol_directory_message::fields_type, expiry_month) == 134, "unexpected offset of options_symbol_directory_message::fields_type::expiry_month");
static_assert(offsetof(options_symbol_directory_message::fields_type, option_type) == 135, "unexpected offset of options_symbol_directory_message::fields_type::option_type");
static_assert(offsetof(options_symbol_directory_message::fields_type, strike) == 136, "unexpected offset of options_symbol_directory_message::fields_type::strike");
static_assert(offsetof(options_symbol_directory_message::fields_type, underlying_tradeable_instrument_id) == 144, "unexpected offset of options_symbol_directory_message::fields_type::underlying_tradeable_instrument_id");
static_assert(offsetof(options_symbol_directory_message::fields_type, price_display_decimals) == 148, "unexpected offset of options_symbol_directory_message::fields_type::price_display_decimals");
static_assert(offsetof(options_symbol_directory_message::fields_type, price_fractional_denominator) == 149, "unexpected offset of options_symbol_directory_message::fields_type::price_fractional_denominator");
static_assert(offsetof(options_symbol_directory_message::fields_type, price_minimum_tick) == 153, "unexpected offset of options_symbol_directory_message::fields_type::price_minimum_tick");
static_assert(offsetof(options_symbol_directory_message::fields_type, strike_price_decimal_position) == 157, "unexpected offset of options_symbol_directory_message::fields_type::strike_price_decimal_position");
static_assert(offsetof(options_symbol_directory_message::fields_type, strike_price_fractional_denominator) == 158, "unexpected offset of options_symbol_directory_message::fields_type::strike_price_fractional_denominator");
static_assert(offsetof(options_symbol_directory_message::fields_type, strike_price_minimum_tick) == 162, "unexpected offset of options_symbol_directory_message::fields_type::strike_price_minimum_tick");
static_assert(offsetof(options_symbol_directory_message::fields_type, last_trading_date) == 166, "unexpected offset of options_symbol_directory_message::fields_type::last_trading_date");
static_assert(offsetof(options_symbol_directory_message::fields_type, prior_day_settlement) == 170, "unexpected offset of options_symbol_directory_message::fields_type::prior_day_settlement");
static_assert(offsetof(options_symbol_directory_message::fields_type, volatility) == 178, "unexpected offset of options_symbol_directory_message::fields_type::volatility");
static_assert(offsetof(options_symbol_directory_message::fields_type, currency) == 186, "unexpected offset of options_symbol_directory_message::fields_type::currency");
static_assert(offsetof(options_symbol_directory_message::fields_type, lot_size_or_face_value) == 189, "unexpected offset of options_symbol_directory_message::fields_type::lot_size_or_face_value");
static_assert(offsetof(options_symbol_directory_message::fields_type, maturity_value) == 197, "unexpected offset of options_symbol_directory_message::fields_type::maturity_value");
static_assert(offsetof(options_symbol_directory_message::fields_type, coupon_rate) == 198, "unexpected offset of options_symbol_directory_message::fields_type::coupon_rate");
static_assert(offsetof(options_symbol_directory_message::fields_type, payments_per_year) == 200, "unexpected offset of options_symbol_directory_message::fields_type::payments_per_year");
static_assert(offsetof(options_symbol_directory_message::fields_type, block_lot_size) == 201, "unexpected offset of options_symbol_directory_message::fields_type::block_lot_size");
static_assert(offsetof(options_symbol_directory_message::fields_type, expiry_date) == 205, "unexpected offset of options_symbol_directory_message::fields_type::expiry_date");
static_assert(offsetof(options_symbol_directory_message::fields_type, basis_of_quotation) == 209, "unexpected offset of options_symbol_directory_message::fields_type::basis_of_quotation");
static_assert(sizeof(options_symbol_directory_message::fields_type) == 219, "unexpected sizeof options_symbol_directory_message::fields_type");
static_assert(sizeof(options_symbol_directory_message) == sizeof(itch_ntp::message_header) + 219, "unexpected sizeof options_symbol_directory_message");

#pragma pack(pop)
}
