#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDay.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionClosingType.hpp"
#include "../types/Tradable.hpp"
#include "../types/Mpv.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Options Directory Message
struct options_directory_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::security_symbol security_symbol;
        itch_topofmarket::expiration_year expiration_year;
        itch_topofmarket::expiration_month expiration_month;
        itch_topofmarket::expiration_day expiration_day;
        itch_topofmarket::strike_price strike_price;
        itch_topofmarket::option_type option_type;
        itch_topofmarket::source source;
        itch_topofmarket::underlying_symbol underlying_symbol;
        itch_topofmarket::option_closing_type option_closing_type;
        itch_topofmarket::tradable tradable;
        itch_topofmarket::mpv mpv;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::options_directory_message};

    fields_type fields;

    // parse method
    static options_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_directory_message*>(buffer);
    }

    // parse method const
    static const options_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_directory_message::fields_type, nanoseconds) == 0, "unexpected offset of options_directory_message::fields_type::nanoseconds");
static_assert(offsetof(options_directory_message::fields_type, option_id) == 4, "unexpected offset of options_directory_message::fields_type::option_id");
static_assert(offsetof(options_directory_message::fields_type, security_symbol) == 8, "unexpected offset of options_directory_message::fields_type::security_symbol");
static_assert(offsetof(options_directory_message::fields_type, expiration_year) == 14, "unexpected offset of options_directory_message::fields_type::expiration_year");
static_assert(offsetof(options_directory_message::fields_type, expiration_month) == 15, "unexpected offset of options_directory_message::fields_type::expiration_month");
static_assert(offsetof(options_directory_message::fields_type, expiration_day) == 16, "unexpected offset of options_directory_message::fields_type::expiration_day");
static_assert(offsetof(options_directory_message::fields_type, strike_price) == 17, "unexpected offset of options_directory_message::fields_type::strike_price");
static_assert(offsetof(options_directory_message::fields_type, option_type) == 21, "unexpected offset of options_directory_message::fields_type::option_type");
static_assert(offsetof(options_directory_message::fields_type, source) == 22, "unexpected offset of options_directory_message::fields_type::source");
static_assert(offsetof(options_directory_message::fields_type, underlying_symbol) == 23, "unexpected offset of options_directory_message::fields_type::underlying_symbol");
static_assert(offsetof(options_directory_message::fields_type, option_closing_type) == 36, "unexpected offset of options_directory_message::fields_type::option_closing_type");
static_assert(offsetof(options_directory_message::fields_type, tradable) == 37, "unexpected offset of options_directory_message::fields_type::tradable");
static_assert(offsetof(options_directory_message::fields_type, mpv) == 38, "unexpected offset of options_directory_message::fields_type::mpv");
static_assert(sizeof(options_directory_message::fields_type) == 39, "unexpected sizeof options_directory_message::fields_type");
static_assert(sizeof(options_directory_message) == sizeof(itch_topofmarket::message_header) + 39, "unexpected sizeof options_directory_message");

#pragma pack(pop)
}
