#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SymbolName.hpp"
#include "../types/LongName.hpp"
#include "../types/CfiCode.hpp"
#include "../types/PriceMethod.hpp"
#include "../types/PriceDisplayDecimals.hpp"
#include "../types/PriceFractionalDenominator.hpp"
#include "../types/PriceMinimumTick.hpp"
#include "../types/Legs.hpp"
#include "../structs/CombinationLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Combination Symbol Directory Message
struct combination_symbol_directory_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::symbol_name symbol_name;
        itch_ntp::long_name long_name;
        itch_ntp::cfi_code cfi_code;
        itch_ntp::price_method price_method;
        itch_ntp::price_display_decimals price_display_decimals;
        itch_ntp::price_fractional_denominator price_fractional_denominator;
        itch_ntp::price_minimum_tick price_minimum_tick;
        itch_ntp::legs legs;
        itch_ntp::combination_leg combination_leg[6];
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::combination_symbol_directory_message};

    fields_type fields;

    // parse method
    static combination_symbol_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<combination_symbol_directory_message*>(buffer);
    }

    // parse method const
    static const combination_symbol_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const combination_symbol_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(combination_symbol_directory_message::fields_type, nanoseconds) == 0, "unexpected offset of combination_symbol_directory_message::fields_type::nanoseconds");
static_assert(offsetof(combination_symbol_directory_message::fields_type, trade_date) == 4, "unexpected offset of combination_symbol_directory_message::fields_type::trade_date");
static_assert(offsetof(combination_symbol_directory_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of combination_symbol_directory_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(combination_symbol_directory_message::fields_type, symbol_name) == 10, "unexpected offset of combination_symbol_directory_message::fields_type::symbol_name");
static_assert(offsetof(combination_symbol_directory_message::fields_type, long_name) == 42, "unexpected offset of combination_symbol_directory_message::fields_type::long_name");
static_assert(offsetof(combination_symbol_directory_message::fields_type, cfi_code) == 102, "unexpected offset of combination_symbol_directory_message::fields_type::cfi_code");
static_assert(offsetof(combination_symbol_directory_message::fields_type, price_method) == 108, "unexpected offset of combination_symbol_directory_message::fields_type::price_method");
static_assert(offsetof(combination_symbol_directory_message::fields_type, price_display_decimals) == 109, "unexpected offset of combination_symbol_directory_message::fields_type::price_display_decimals");
static_assert(offsetof(combination_symbol_directory_message::fields_type, price_fractional_denominator) == 110, "unexpected offset of combination_symbol_directory_message::fields_type::price_fractional_denominator");
static_assert(offsetof(combination_symbol_directory_message::fields_type, price_minimum_tick) == 114, "unexpected offset of combination_symbol_directory_message::fields_type::price_minimum_tick");
static_assert(offsetof(combination_symbol_directory_message::fields_type, legs) == 118, "unexpected offset of combination_symbol_directory_message::fields_type::legs");
static_assert(offsetof(combination_symbol_directory_message::fields_type, combination_leg) == 119, "unexpected offset of combination_symbol_directory_message::fields_type::combination_leg");
static_assert(sizeof(combination_symbol_directory_message::fields_type) == 221, "unexpected sizeof combination_symbol_directory_message::fields_type");
static_assert(sizeof(combination_symbol_directory_message) == sizeof(itch_ntp::message_header) + 221, "unexpected sizeof combination_symbol_directory_message");

#pragma pack(pop)
}
