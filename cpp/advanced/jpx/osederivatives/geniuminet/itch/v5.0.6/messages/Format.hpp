#pragma once

#include <ostream>
#include <string_view>
#include <cstddef>
#include <string>

#include "SecondsMessage.hpp"
#include "OrderBookDirectory.hpp"
#include "CombinationOrderbookLeg.hpp"
#include "TickSizeTableEntry.hpp"
#include "SystemEventMessage.hpp"
#include "OrderBookStateMessage.hpp"
#include "AddOrderNoMpid.hpp"
#include "AddOrderWithMpid.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedWithPriceMessage.hpp"
#include "OrderReplaceMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "TradeMessage.hpp"
#include "EquilibriumPriceUpdate.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

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
       << ",message_type=\"" << itch_geniuminet::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const seconds_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_directory& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",symbol=\"" << text::latin1_to_utf8(msg.fields.symbol.get_trimmed().value()) << '"'
       << ",long_name=\"" << text::latin1_to_utf8(msg.fields.long_name.get_trimmed().value()) << '"'
       << ",isin=\"" << text::latin1_to_utf8(msg.fields.isin.get_trimmed().value()) << '"'
       << ",financial_product=\"" << itch_geniuminet::financial_product::to_string(msg.fields.financial_product.get().value()) << '"'
       << ",trading_currency=\"" << text::latin1_to_utf8(msg.fields.trading_currency.get_trimmed().value()) << '"'
       << ",decimals_in_price=" << msg.fields.decimals_in_price.get().value()
       << ",decimals_in_nominal_value=" << msg.fields.decimals_in_nominal_value.get().value()
       << ",odd_lot_size=" << msg.fields.odd_lot_size.get().value()
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",block_lot_size=" << msg.fields.block_lot_size.get().value()
       << ",nominal_value=" << msg.fields.nominal_value.get().value()
       << ",number_of_legs=" << static_cast<unsigned>(msg.fields.number_of_legs.get().value())
       << ",underlying_orderbook_id=" << msg.fields.underlying_orderbook_id.get().value()
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",expiration_date=" << msg.fields.expiration_date.get().value()
       << ",decimals_in_strike_price=" << msg.fields.decimals_in_strike_price.get().value()
       << ",put_or_call=\"" << itch_geniuminet::put_or_call::to_string(msg.fields.put_or_call.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const combination_orderbook_leg& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",combination_orderbook_id=" << msg.fields.combination_orderbook_id.get().value()
       << ",leg_orderbook_id=" << msg.fields.leg_orderbook_id.get().value()
       << ",leg_side=\"" << itch_geniuminet::leg_side::to_string(msg.fields.leg_side.get().value()) << '"'
       << ",leg_ratio=" << msg.fields.leg_ratio.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const tick_size_table_entry& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",tick_size=" << msg.fields.tick_size.get().value()
       << ",price_from=" << msg.fields.price_from.get().value()
       << ",price_to=" << msg.fields.price_to.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",event_code=\"" << itch_geniuminet::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",state_name=\"" << text::latin1_to_utf8(msg.fields.state_name.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_no_mpid& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_book_position=" << msg.fields.order_book_position.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",order_attributes=" << static_cast<unsigned>(msg.fields.order_attributes.get().value())
       << ",lot_type=\"" << itch_geniuminet::lot_type::to_string(msg.fields.lot_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_with_mpid& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",order_book_position=" << msg.fields.order_book_position.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",order_attributes=" << static_cast<unsigned>(msg.fields.order_attributes.get().value())
       << ",lot_type=\"" << itch_geniuminet::lot_type::to_string(msg.fields.lot_type.get().value()) << '"'
       << ",participant_id=\"" << text::latin1_to_utf8(msg.fields.participant_id.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       << ",combo_group_id=" << msg.fields.combo_group_id.get().value()
       << ",participant_id_owner=\"" << text::latin1_to_utf8(msg.fields.participant_id_owner.get_trimmed().value()) << '"'
       << ",participant_id_counterparty=\"" << text::latin1_to_utf8(msg.fields.participant_id_counterparty.get_trimmed().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_with_price_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       << ",combo_group_id=" << msg.fields.combo_group_id.get().value()
       << ",owner_participant_id=\"" << text::latin1_to_utf8(msg.fields.owner_participant_id.get_trimmed().value()) << '"'
       << ",counterparty_participant_id=\"" << text::latin1_to_utf8(msg.fields.counterparty_participant_id.get_trimmed().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",occurred_at_cross=\"" << itch_geniuminet::occurred_at_cross::to_string(msg.fields.occurred_at_cross.get().value()) << '"'
       << ",printable=\"" << itch_geniuminet::printable::to_string(msg.fields.printable.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_replace_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",new_orderbook_position=" << msg.fields.new_orderbook_position.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",order_attributes=" << static_cast<unsigned>(msg.fields.order_attributes.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",match_id=" << msg.fields.match_id.get().value()
       << ",combo_group_id=" << msg.fields.combo_group_id.get().value()
       << ",side=\"" << itch_geniuminet::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",owner_participant_id=\"" << text::latin1_to_utf8(msg.fields.owner_participant_id.get_trimmed().value()) << '"'
       << ",counterparty_participant_id=\"" << text::latin1_to_utf8(msg.fields.counterparty_participant_id.get_trimmed().value()) << '"'
       << ",printable=\"" << itch_geniuminet::printable::to_string(msg.fields.printable.get().value()) << '"'
       << ",occurred_at_cross=\"" << itch_geniuminet::occurred_at_cross::to_string(msg.fields.occurred_at_cross.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const equilibrium_price_update& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_book_id=" << msg.fields.order_book_id.get().value()
       << ",available_bid_quantity_at_equilibrium_price=" << msg.fields.available_bid_quantity_at_equilibrium_price.get().value()
       << ",available_ask_quantity_at_equilibrium_price=" << msg.fields.available_ask_quantity_at_equilibrium_price.get().value()
       << ",equilibrium_price=" << msg.fields.equilibrium_price.get().value()
       ;
    return os;
}

}
