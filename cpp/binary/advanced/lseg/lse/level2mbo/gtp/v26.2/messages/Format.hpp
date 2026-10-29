#pragma once

#include <ostream>
#include <string_view>
#include <cstddef>
#include <string>

#include "SystemEventMessage.hpp"
#include "InstrumentDirectoryMessage.hpp"
#include "InstrumentStatusMessage.hpp"
#include "AddOrderMboMessage.hpp"
#include "AddOrderShortMboMessage.hpp"
#include "OrderBookClearMessage.hpp"
#include "TradeMessage.hpp"
#include "StatisticsMessage.hpp"
#include "StatisticsUpdateMessage.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

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

inline std::ostream& operator<<(std::ostream& os, const unit_header& value) {
    os << "length=" << value.length.get().value()
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",market_data_group=\"" << value.market_data_group.get().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << gtp_level2mbo::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",event_code=\"" << gtp_level2mbo::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_directory_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",isin=\"" << (msg.fields.isin.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.isin.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",allowed_book_types=" << static_cast<unsigned>(msg.fields.allowed_book_types.get().value())
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",venue_instrument_id=\"" << (msg.fields.venue_instrument_id.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.venue_instrument_id.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",tick_id=\"" << (msg.fields.tick_id.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.tick_id.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",dynamic_circuit_breaker_tolerances=" << msg.fields.dynamic_circuit_breaker_tolerances.get().value()
       << ",static_circuit_breaker_tolerances=" << msg.fields.static_circuit_breaker_tolerances.get().value()
       << ",segment=\"" << (msg.fields.segment.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.segment.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",currency=\"" << (msg.fields.currency.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.currency.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",partition_id=\"" << (msg.fields.partition_id.get().has_value() ? std::string_view(1, msg.fields.partition_id.get().value()) : std::string_view("null")) << '"'
       << ",average_daily_turnover_adt=" << msg.fields.average_daily_turnover_adt.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_status_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",trading_status=\"" << gtp_level2mbo::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",session_change_reason=\"" << gtp_level2mbo::session_change_reason::to_string(msg.fields.session_change_reason.get().value()) << '"'
       << ",new_end_time=\"" << (msg.fields.new_end_time.get_trimmed().has_value() ? msg.fields.new_end_time.get_trimmed().value() : std::string_view("null")) << '"'
       << ",order_book_type=\"" << gtp_level2mbo::order_book_type::to_string(msg.fields.order_book_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_mbo_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << gtp_level2mbo::side::to_string(msg.fields.side.get().value()) << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",order_book_type=\"" << gtp_level2mbo::order_book_type::to_string(msg.fields.order_book_type.get().value()) << '"'
       << ",participant=\"" << (msg.fields.participant.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.participant.get_trimmed().value()) : std::string_view("null")) << '"'
       << ",depth=" << static_cast<unsigned>(msg.fields.depth.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_short_mbo_message& msg) {
    os << "order_id=" << msg.fields.order_id.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",participant=\"" << (msg.fields.participant.get_trimmed().has_value() ? text::windows1252_to_utf8(msg.fields.participant.get_trimmed().value()) : std::string_view("null")) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_clear_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",order_book_type=\"" << gtp_level2mbo::order_book_type::to_string(msg.fields.order_book_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",transaction_time=" << msg.fields.transaction_time.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",executed_size=" << msg.fields.executed_size.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",trade_type=\"" << gtp_level2mbo::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",auction_type=\"" << gtp_level2mbo::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",trade_flags=" << static_cast<unsigned>(msg.fields.trade_flags.get().value())
       << ",hidden_execution_indicator=\"" << gtp_level2mbo::hidden_execution_indicator::to_string(msg.fields.hidden_execution_indicator.get().value()) << '"'
       << ",trade_qualifier=\"" << gtp_level2mbo::trade_qualifier::to_string(msg.fields.trade_qualifier.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const statistics_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",volume=" << msg.fields.volume.get().value()
       << ",volume_on_book_only=" << msg.fields.volume_on_book_only.get().value()
       << ",vwap=" << msg.fields.vwap.get().value()
       << ",vwap_on_book_only=" << msg.fields.vwap_on_book_only.get().value()
       << ",number_of_trades=" << msg.fields.number_of_trades.get().value()
       << ",number_of_trades_on_book_only=" << msg.fields.number_of_trades_on_book_only.get().value()
       << ",turnover=" << msg.fields.turnover.get().value()
       << ",turnover_on_book_only=" << msg.fields.turnover_on_book_only.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const statistics_update_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",instrument=" << msg.fields.instrument.get().value()
       << ",source_venue=\"" << gtp_level2mbo::source_venue::to_string(msg.fields.source_venue.get().value()) << '"'
       << ",statistic_type=\"" << gtp_level2mbo::statistic_type::to_string(msg.fields.statistic_type.get().value()) << '"'
       << ",statistic_price=" << msg.fields.statistic_price.get().value()
       << ",statistic_size=" << msg.fields.statistic_size.get().value()
       << ",auction_type=\"" << gtp_level2mbo::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",imbalance_quantity=" << msg.fields.imbalance_quantity.get().value()
       << ",auction_info=\"" << gtp_level2mbo::auction_info::to_string(msg.fields.auction_info.get().value()) << '"'
       << ",opening_closing_price_indicator=\"" << gtp_level2mbo::opening_closing_price_indicator::to_string(msg.fields.opening_closing_price_indicator.get().value()) << '"'
       ;
    return os;
}

}
