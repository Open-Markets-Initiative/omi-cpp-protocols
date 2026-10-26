#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationYear.hpp"
#include "../types/ExpirationMonth.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/ExplicitStrikePrice.hpp"
#include "../types/OptionType.hpp"
#include "../types/Source.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionsClosingType.hpp"
#include "../types/Tradable.hpp"
#include "../types/Mpv.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Options Directory Message
struct options_directory_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::option_id option_id;
        itch_itto::security_symbol security_symbol;
        itch_itto::expiration_year expiration_year;
        itch_itto::expiration_month expiration_month;
        itch_itto::expiration_date expiration_date;
        itch_itto::explicit_strike_price explicit_strike_price;
        itch_itto::option_type option_type;
        itch_itto::source source;
        itch_itto::underlying_symbol underlying_symbol;
        itch_itto::options_closing_type options_closing_type;
        itch_itto::tradable tradable;
        itch_itto::mpv mpv;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::options_directory_message};

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
static_assert(offsetof(options_directory_message::fields_type, tracking_number) == 0, "unexpected offset of options_directory_message::fields_type::tracking_number");
static_assert(offsetof(options_directory_message::fields_type, timestamp) == 2, "unexpected offset of options_directory_message::fields_type::timestamp");
static_assert(offsetof(options_directory_message::fields_type, option_id) == 8, "unexpected offset of options_directory_message::fields_type::option_id");
static_assert(offsetof(options_directory_message::fields_type, security_symbol) == 12, "unexpected offset of options_directory_message::fields_type::security_symbol");
static_assert(offsetof(options_directory_message::fields_type, expiration_year) == 18, "unexpected offset of options_directory_message::fields_type::expiration_year");
static_assert(offsetof(options_directory_message::fields_type, expiration_month) == 19, "unexpected offset of options_directory_message::fields_type::expiration_month");
static_assert(offsetof(options_directory_message::fields_type, expiration_date) == 20, "unexpected offset of options_directory_message::fields_type::expiration_date");
static_assert(offsetof(options_directory_message::fields_type, explicit_strike_price) == 21, "unexpected offset of options_directory_message::fields_type::explicit_strike_price");
static_assert(offsetof(options_directory_message::fields_type, option_type) == 25, "unexpected offset of options_directory_message::fields_type::option_type");
static_assert(offsetof(options_directory_message::fields_type, source) == 26, "unexpected offset of options_directory_message::fields_type::source");
static_assert(offsetof(options_directory_message::fields_type, underlying_symbol) == 27, "unexpected offset of options_directory_message::fields_type::underlying_symbol");
static_assert(offsetof(options_directory_message::fields_type, options_closing_type) == 40, "unexpected offset of options_directory_message::fields_type::options_closing_type");
static_assert(offsetof(options_directory_message::fields_type, tradable) == 41, "unexpected offset of options_directory_message::fields_type::tradable");
static_assert(offsetof(options_directory_message::fields_type, mpv) == 42, "unexpected offset of options_directory_message::fields_type::mpv");
static_assert(sizeof(options_directory_message::fields_type) == 43, "unexpected sizeof options_directory_message::fields_type");
static_assert(sizeof(options_directory_message) == sizeof(itch_itto::message_header) + 43, "unexpected sizeof options_directory_message");

#pragma pack(pop)
}
