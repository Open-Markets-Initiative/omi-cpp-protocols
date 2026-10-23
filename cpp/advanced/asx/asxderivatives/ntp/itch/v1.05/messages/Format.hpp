#pragma once

#include <ostream>
#include <string_view>
#include <cstddef>
#include <string>

#include "SecondsMessage.hpp"
#include "EndOfBusinessTradeDateMessage.hpp"
#include "FutureSymbolDirectoryMessage.hpp"
#include "OptionsSymbolDirectoryMessage.hpp"
#include "CombinationSymbolDirectoryMessage.hpp"
#include "BundlesSymbolDirectory.hpp"
#include "OrderBookStateMessage.hpp"
#include "AddOrderMessage.hpp"
#include "OrderVolumeCancelledMessage.hpp"
#include "OrderDeletedMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "AuctionOrderExecutedMessage.hpp"
#include "CombinationOrderExecutedMessage.hpp"
#include "ImpliedOrderAddedMessage.hpp"
#include "ImpliedOrderReplacedMessage.hpp"
#include "ImpliedOrderDeletedMessage.hpp"
#include "TradeExecutedMessage.hpp"
#include "CombinationTradeExecutedMessage.hpp"
#include "TradeCancellationMessage.hpp"
#include "EquilibriumPriceMessage.hpp"
#include "OpenHighLowLastTradeAdjustmentMessage.hpp"
#include "MarketSettlementMessage.hpp"
#include "TextMessage.hpp"
#include "RequestForQuoteMessage.hpp"
#include "AnomalousOrderThresholdPublishMessage.hpp"
#include "VolumeAndOpenInterestMessage.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

// Text as UTF-8, from the encoding its field states. Ascii and UTF-8 text is UTF-8 already
// and is written as it is read; these read the encodings that are not.
namespace text {

// A code point as UTF-8
inline void append_utf8(std::string& out, char32_t code) {
    if (code < 0x80) {
        out += static_cast<char>(code);
    } else if (code < 0x800) {
        out += static_cast<char>(0xC0 | (code >> 6));
        out += static_cast<char>(0x80 | (code & 0x3F));
    } else if (code < 0x10000) {
        out += static_cast<char>(0xE0 | (code >> 12));
        out += static_cast<char>(0x80 | ((code >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (code & 0x3F));
    } else {
        out += static_cast<char>(0xF0 | (code >> 18));
        out += static_cast<char>(0x80 | ((code >> 12) & 0x3F));
        out += static_cast<char>(0x80 | ((code >> 6) & 0x3F));
        out += static_cast<char>(0x80 | (code & 0x3F));
    }
}

// ISO 8859-1 (Latin-1): every byte is the code point of the same value
inline char32_t latin1_code(unsigned char byte) {
    return byte;
}

// Windows-1252: Latin-1 but for 0x80 to 0x9F, which carry punctuation and letters; the five
// bytes the code page leaves unassigned keep their own value
inline char32_t windows1252_code(unsigned char byte) {
    static constexpr char32_t high[32] = {
        0x20AC, 0x0081, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
        0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x008D, 0x017D, 0x008F,
        0x0090, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
        0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x009D, 0x017E, 0x0178,
    };
    if (byte >= 0x80 && byte < 0xA0) { return high[byte - 0x80]; }
    return byte;
}

// ISO 8859-9 (Latin-5): Latin-1 with six Turkish letters in place of Icelandic ones
inline char32_t latin5_code(unsigned char byte) {
    switch (byte) {
        case 0xD0: return 0x011E;
        case 0xDD: return 0x0130;
        case 0xDE: return 0x015E;
        case 0xF0: return 0x011F;
        case 0xFD: return 0x0131;
        case 0xFE: return 0x015F;
        default: return byte;
    }
}

// Text of one byte to the character, as UTF-8
template <typename Code>
std::string bytes_to_utf8(std::string_view bytes, Code code) {
    std::string out;
    out.reserve(bytes.size());
    for (const auto byte : bytes) { append_utf8(out, code(static_cast<unsigned char>(byte))); }
    return out;
}

inline std::string latin1_to_utf8(std::string_view bytes) { return bytes_to_utf8(bytes, latin1_code); }
inline std::string latin1_to_utf8(char character) { return latin1_to_utf8(std::string_view(&character, 1)); }
inline std::string windows1252_to_utf8(std::string_view bytes) { return bytes_to_utf8(bytes, windows1252_code); }
inline std::string windows1252_to_utf8(char character) { return windows1252_to_utf8(std::string_view(&character, 1)); }
inline std::string latin5_to_utf8(std::string_view bytes) { return bytes_to_utf8(bytes, latin5_code); }
inline std::string latin5_to_utf8(char character) { return latin5_to_utf8(std::string_view(&character, 1)); }

// UTF-16, two bytes to the code unit in the order the field states: a surrogate pair is one
// code point, a surrogate left unpaired is the replacement character, and an odd last byte is
// not a code unit
inline std::string utf16_to_utf8(std::string_view bytes, bool little) {
    const auto unit = [&](std::size_t at) -> char32_t {
        const auto first = static_cast<unsigned char>(bytes[at]);
        const auto second = static_cast<unsigned char>(bytes[at + 1]);
        if (little) { return static_cast<char32_t>(second << 8 | first); }
        return static_cast<char32_t>(first << 8 | second);
    };
    std::string out;
    out.reserve(bytes.size());
    for (std::size_t at = 0; at + 1 < bytes.size(); at += 2) {
        auto code = unit(at);
        if (code >= 0xD800 && code < 0xDC00 && at + 3 < bytes.size()) {
            const auto low = unit(at + 2);
            if (low >= 0xDC00 && low < 0xE000) {
                code = 0x10000 + ((code - 0xD800) << 10) + (low - 0xDC00);
                at += 2;
            }
        }
        if (code >= 0xD800 && code < 0xE000) { code = 0xFFFD; }
        append_utf8(out, code);
    }
    return out;
}

inline std::string utf16le_to_utf8(std::string_view bytes) { return utf16_to_utf8(bytes, true); }
inline std::string utf16be_to_utf8(std::string_view bytes) { return utf16_to_utf8(bytes, false); }

} // namespace text

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_ntp::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const seconds_message& msg) {
    os << "second=" << msg.fields.second.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_business_trade_date_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",event_code=\"" << itch_ntp::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const future_symbol_directory_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",symbol_name=\"" << text::latin1_to_utf8(msg.fields.symbol_name.get_trimmed().value()) << '"'
       << ",long_name=\"" << text::latin1_to_utf8(msg.fields.long_name.get_trimmed().value()) << '"'
       << ",isin=\"" << text::latin1_to_utf8(msg.fields.isin.get_trimmed().value()) << '"'
       << ",exchange=\"" << text::latin1_to_utf8(msg.fields.exchange.get_trimmed().value()) << '"'
       << ",instrument=\"" << text::latin1_to_utf8(msg.fields.instrument.get_trimmed().value()) << '"'
       << ",cfi_code=\"" << text::latin1_to_utf8(msg.fields.cfi_code.get_trimmed().value()) << '"'
       << ",expiry_year=" << msg.fields.expiry_year.get().value()
       << ",expiry_month=\"" << itch_ntp::expiry_month::to_string(msg.fields.expiry_month.get().value()) << '"'
       << ",price_display_decimals=" << static_cast<unsigned>(msg.fields.price_display_decimals.get().value())
       << ",price_fractional_denominator=" << msg.fields.price_fractional_denominator.get().value()
       << ",price_minimum_tick=" << msg.fields.price_minimum_tick.get().value()
       << ",last_trading_date=" << msg.fields.last_trading_date.get().value()
       << ",prior_day_settlement=" << msg.fields.prior_day_settlement.get().value()
       << ",currency=\"" << text::latin1_to_utf8(msg.fields.currency.get_trimmed().value()) << '"'
       << ",lot_size_or_face_value=" << msg.fields.lot_size_or_face_value.get().value()
       << ",maturity_value=" << static_cast<unsigned>(msg.fields.maturity_value.get().value())
       << ",coupon_rate=" << msg.fields.coupon_rate.get().value()
       << ",payments_per_year=" << static_cast<unsigned>(msg.fields.payments_per_year.get().value())
       << ",block_lot_size=" << msg.fields.block_lot_size.get().value()
       << ",expiry_date=" << msg.fields.expiry_date.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_symbol_directory_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",symbol_name=\"" << text::latin1_to_utf8(msg.fields.symbol_name.get_trimmed().value()) << '"'
       << ",long_name=\"" << text::latin1_to_utf8(msg.fields.long_name.get_trimmed().value()) << '"'
       << ",isin=\"" << text::latin1_to_utf8(msg.fields.isin.get_trimmed().value()) << '"'
       << ",exchange=\"" << text::latin1_to_utf8(msg.fields.exchange.get_trimmed().value()) << '"'
       << ",instrument=\"" << text::latin1_to_utf8(msg.fields.instrument.get_trimmed().value()) << '"'
       << ",cfi_code=\"" << text::latin1_to_utf8(msg.fields.cfi_code.get_trimmed().value()) << '"'
       << ",expiry_year=" << msg.fields.expiry_year.get().value()
       << ",expiry_month=\"" << itch_ntp::expiry_month::to_string(msg.fields.expiry_month.get().value()) << '"'
       << ",option_type=\"" << itch_ntp::option_type::to_string(msg.fields.option_type.get().value()) << '"'
       << ",strike=" << msg.fields.strike.get().value()
       << ",underlying_tradeable_instrument_id=" << msg.fields.underlying_tradeable_instrument_id.get().value()
       << ",price_display_decimals=" << static_cast<unsigned>(msg.fields.price_display_decimals.get().value())
       << ",price_fractional_denominator=" << msg.fields.price_fractional_denominator.get().value()
       << ",price_minimum_tick=" << msg.fields.price_minimum_tick.get().value()
       << ",strike_price_decimal_position=" << static_cast<unsigned>(msg.fields.strike_price_decimal_position.get().value())
       << ",strike_price_fractional_denominator=" << msg.fields.strike_price_fractional_denominator.get().value()
       << ",strike_price_minimum_tick=" << msg.fields.strike_price_minimum_tick.get().value()
       << ",last_trading_date=" << msg.fields.last_trading_date.get().value()
       << ",prior_day_settlement=" << msg.fields.prior_day_settlement.get().value()
       << ",volatility=" << msg.fields.volatility.get().value()
       << ",currency=\"" << text::latin1_to_utf8(msg.fields.currency.get_trimmed().value()) << '"'
       << ",lot_size_or_face_value=" << msg.fields.lot_size_or_face_value.get().value()
       << ",maturity_value=" << static_cast<unsigned>(msg.fields.maturity_value.get().value())
       << ",coupon_rate=" << msg.fields.coupon_rate.get().value()
       << ",payments_per_year=" << static_cast<unsigned>(msg.fields.payments_per_year.get().value())
       << ",block_lot_size=" << msg.fields.block_lot_size.get().value()
       << ",expiry_date=" << msg.fields.expiry_date.get().value()
       << ",basis_of_quotation=\"" << text::latin1_to_utf8(msg.fields.basis_of_quotation.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const combination_symbol_directory_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",symbol_name=\"" << text::latin1_to_utf8(msg.fields.symbol_name.get_trimmed().value()) << '"'
       << ",long_name=\"" << text::latin1_to_utf8(msg.fields.long_name.get_trimmed().value()) << '"'
       << ",cfi_code=\"" << text::latin1_to_utf8(msg.fields.cfi_code.get_trimmed().value()) << '"'
       << ",price_method=\"" << itch_ntp::price_method::to_string(msg.fields.price_method.get().value()) << '"'
       << ",price_display_decimals=" << static_cast<unsigned>(msg.fields.price_display_decimals.get().value())
       << ",price_fractional_denominator=" << msg.fields.price_fractional_denominator.get().value()
       << ",price_minimum_tick=" << msg.fields.price_minimum_tick.get().value()
       << ",legs=" << static_cast<unsigned>(msg.fields.legs.get().value())
       << ",combination_leg.tradeable_instrument_id_leg=" << msg.fields.combination_leg.tradeable_instrument_id_leg.get().value()
       << ",combination_leg.side_leg=\"" << itch_ntp::side_leg::to_string(msg.fields.combination_leg.side_leg.get().value()) << '"'
       << ",combination_leg.ratio_leg=" << msg.fields.combination_leg.ratio_leg.get().value()
       << ",combination_leg.price_leg=" << msg.fields.combination_leg.price_leg.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const bundles_symbol_directory& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",symbol_name=\"" << text::latin1_to_utf8(msg.fields.symbol_name.get_trimmed().value()) << '"'
       << ",long_name=\"" << text::latin1_to_utf8(msg.fields.long_name.get_trimmed().value()) << '"'
       << ",cfi_code=\"" << text::latin1_to_utf8(msg.fields.cfi_code.get_trimmed().value()) << '"'
       << ",price_method=\"" << itch_ntp::price_method::to_string(msg.fields.price_method.get().value()) << '"'
       << ",price_display_decimals=" << static_cast<unsigned>(msg.fields.price_display_decimals.get().value())
       << ",price_fractional_denominator=" << msg.fields.price_fractional_denominator.get().value()
       << ",price_minimum_tick=" << msg.fields.price_minimum_tick.get().value()
       << ",legs=" << static_cast<unsigned>(msg.fields.legs.get().value())
       << ",bundle_leg.tradeable_instrument_id_leg=" << msg.fields.bundle_leg.tradeable_instrument_id_leg.get().value()
       << ",bundle_leg.side_leg=\"" << itch_ntp::side_leg::to_string(msg.fields.bundle_leg.side_leg.get().value()) << '"'
       << ",bundle_leg.ratio_leg=" << msg.fields.bundle_leg.ratio_leg.get().value()
       << ",bundle_leg.price_leg=" << msg.fields.bundle_leg.price_leg.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",session_state=\"" << itch_ntp::session_state::to_string(msg.fields.session_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_priority=" << msg.fields.order_book_priority.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_volume_cancelled_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_deleted_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_remaining=" << msg.fields.quantity_remaining.get().value()
       << ",trade_type=\"" << itch_ntp::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",combination_trade_id=" << msg.fields.combination_trade_id.get().value()
       << ",counter_party_id=\"" << text::latin1_to_utf8(msg.fields.counter_party_id.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_order_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_remaining=" << msg.fields.quantity_remaining.get().value()
       << ",trade_type=\"" << itch_ntp::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",opposite_order_id=" << msg.fields.opposite_order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const combination_order_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_remaining=" << msg.fields.quantity_remaining.get().value()
       << ",trade_type=\"" << itch_ntp::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",opposite_tradeable_instrument_id=" << msg.fields.opposite_tradeable_instrument_id.get().value()
       << ",opposite_side=\"" << itch_ntp::opposite_side::to_string(msg.fields.opposite_side.get().value()) << '"'
       << ",opposite_order_id=" << msg.fields.opposite_order_id.get().value()
       << ",combination_trade_id=" << msg.fields.combination_trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const implied_order_added_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_priority=" << msg.fields.order_book_priority.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const implied_order_replaced_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_priority=" << msg.fields.order_book_priority.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const implied_order_deleted_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",side=\"" << itch_ntp::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",trade_type=\"" << itch_ntp::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",combination_trade_id=" << msg.fields.combination_trade_id.get().value()
       << ",participant_id_buyer=\"" << text::latin1_to_utf8(msg.fields.participant_id_buyer.get_trimmed().value()) << '"'
       << ",participant_id_seller=\"" << text::latin1_to_utf8(msg.fields.participant_id_seller.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const combination_trade_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",trade_type=\"" << itch_ntp::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",buyer_tradeable_instrument_id=" << msg.fields.buyer_tradeable_instrument_id.get().value()
       << ",buyer_side=\"" << itch_ntp::buyer_side::to_string(msg.fields.buyer_side.get().value()) << '"'
       << ",buyer_order_id=" << msg.fields.buyer_order_id.get().value()
       << ",buyer_combination_trade_id=" << msg.fields.buyer_combination_trade_id.get().value()
       << ",buyer_participant_id=\"" << text::latin1_to_utf8(msg.fields.buyer_participant_id.get_trimmed().value()) << '"'
       << ",seller_tradeable_instrument_id=" << msg.fields.seller_tradeable_instrument_id.get().value()
       << ",seller_side=\"" << itch_ntp::seller_side::to_string(msg.fields.seller_side.get().value()) << '"'
       << ",seller_order_id=" << msg.fields.seller_order_id.get().value()
       << ",seller_combination_trade_id=" << msg.fields.seller_combination_trade_id.get().value()
       << ",seller_participant_id=\"" << text::latin1_to_utf8(msg.fields.seller_participant_id.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancellation_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const equilibrium_price_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",equilibrium_price=" << msg.fields.equilibrium_price.get().value()
       << ",matched_quantity=" << msg.fields.matched_quantity.get().value()
       << ",bid_quantity=" << msg.fields.bid_quantity.get().value()
       << ",ask_quantity=" << msg.fields.ask_quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const open_high_low_last_trade_adjustment_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",opening_trade=" << msg.fields.opening_trade.get().value()
       << ",highest_trade=" << msg.fields.highest_trade.get().value()
       << ",lowest_trade=" << msg.fields.lowest_trade.get().value()
       << ",last_trade=" << msg.fields.last_trade.get().value()
       << ",last_volume=" << msg.fields.last_volume.get().value()
       << ",total_traded_volume=" << msg.fields.total_traded_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_settlement_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",opening_trade=" << msg.fields.opening_trade.get().value()
       << ",highest_trade=" << msg.fields.highest_trade.get().value()
       << ",lowest_trade=" << msg.fields.lowest_trade.get().value()
       << ",last_trade=" << msg.fields.last_trade.get().value()
       << ",last_volume=" << msg.fields.last_volume.get().value()
       << ",total_traded_volume=" << msg.fields.total_traded_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const text_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",source_id=\"" << text::latin1_to_utf8(msg.fields.source_id.get_trimmed().value()) << '"'
       << ",text=\"" << text::latin1_to_utf8(msg.fields.text.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const request_for_quote_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",rfq_side=\"" << itch_ntp::rfq_side::to_string(msg.fields.rfq_side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const anomalous_order_threshold_publish_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",aot_price=" << msg.fields.aot_price.get().value()
       << ",aot_upper_price=" << msg.fields.aot_upper_price.get().value()
       << ",aot_lower_price=" << msg.fields.aot_lower_price.get().value()
       << ",etr_price=" << msg.fields.etr_price.get().value()
       << ",etr_upper_price=" << msg.fields.etr_upper_price.get().value()
       << ",etr_lower_price=" << msg.fields.etr_lower_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const volume_and_open_interest_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",trade_date=" << msg.fields.trade_date.get().value()
       << ",tradeable_instrument_id=" << msg.fields.tradeable_instrument_id.get().value()
       << ",cumulative_volume=" << msg.fields.cumulative_volume.get().value()
       << ",open_interest=" << msg.fields.open_interest.get().value()
       << ",voi_trade_date=" << msg.fields.voi_trade_date.get().value()
       ;
    return os;
}

}
