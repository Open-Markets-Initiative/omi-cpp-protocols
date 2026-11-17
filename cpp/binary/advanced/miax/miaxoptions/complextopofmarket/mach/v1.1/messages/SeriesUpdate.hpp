// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/SeriesUpdate.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/CallOrPut.hpp"
#include "../types/OpeningTime.hpp"
#include "../types/ClosingTime.hpp"
#include "../types/RestrictedOption.hpp"
#include "../types/LongTermOption.hpp"
#include "../types/ActiveOnMiax.hpp"
#include "../types/MiaxBboPostingIncrementIndicator.hpp"
#include "../types/LiquidityAcceptanceIncrementIndicator.hpp"
#include "../types/OpeningUnderlyingMarketCode.hpp"
#include "../types/PriorityQuoteWidth.hpp"
#include "../types/Reserved8.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Series Update
struct series_update {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::product_id product_id;
        mach_complextopofmarket::underlying_symbol underlying_symbol;
        mach_complextopofmarket::security_symbol security_symbol;
        mach_complextopofmarket::expiration_date expiration_date;
        mach_complextopofmarket::strike_price strike_price;
        mach_complextopofmarket::call_or_put call_or_put;
        mach_complextopofmarket::opening_time opening_time;
        mach_complextopofmarket::closing_time closing_time;
        mach_complextopofmarket::restricted_option restricted_option;
        mach_complextopofmarket::long_term_option long_term_option;
        mach_complextopofmarket::active_on_miax active_on_miax;
        mach_complextopofmarket::miax_bbo_posting_increment_indicator miax_bbo_posting_increment_indicator;
        mach_complextopofmarket::liquidity_acceptance_increment_indicator liquidity_acceptance_increment_indicator;
        mach_complextopofmarket::opening_underlying_market_code opening_underlying_market_code;
        mach_complextopofmarket::priority_quote_width priority_quote_width;
        mach_complextopofmarket::reserved_8 reserved_8;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::series_update;

    fields_type fields;

    // parse method
    static series_update* parse(std::byte* buffer) {
        return reinterpret_cast<series_update*>(buffer);
    }

    // parse method const
    static const series_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const series_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(series_update::fields_type, nanoseconds) == 0, "unexpected offset of series_update::fields_type::nanoseconds");
static_assert(offsetof(series_update::fields_type, product_id) == 4, "unexpected offset of series_update::fields_type::product_id");
static_assert(offsetof(series_update::fields_type, underlying_symbol) == 8, "unexpected offset of series_update::fields_type::underlying_symbol");
static_assert(offsetof(series_update::fields_type, security_symbol) == 19, "unexpected offset of series_update::fields_type::security_symbol");
static_assert(offsetof(series_update::fields_type, expiration_date) == 25, "unexpected offset of series_update::fields_type::expiration_date");
static_assert(offsetof(series_update::fields_type, strike_price) == 33, "unexpected offset of series_update::fields_type::strike_price");
static_assert(offsetof(series_update::fields_type, call_or_put) == 37, "unexpected offset of series_update::fields_type::call_or_put");
static_assert(offsetof(series_update::fields_type, opening_time) == 38, "unexpected offset of series_update::fields_type::opening_time");
static_assert(offsetof(series_update::fields_type, closing_time) == 46, "unexpected offset of series_update::fields_type::closing_time");
static_assert(offsetof(series_update::fields_type, restricted_option) == 54, "unexpected offset of series_update::fields_type::restricted_option");
static_assert(offsetof(series_update::fields_type, long_term_option) == 55, "unexpected offset of series_update::fields_type::long_term_option");
static_assert(offsetof(series_update::fields_type, active_on_miax) == 56, "unexpected offset of series_update::fields_type::active_on_miax");
static_assert(offsetof(series_update::fields_type, miax_bbo_posting_increment_indicator) == 57, "unexpected offset of series_update::fields_type::miax_bbo_posting_increment_indicator");
static_assert(offsetof(series_update::fields_type, liquidity_acceptance_increment_indicator) == 58, "unexpected offset of series_update::fields_type::liquidity_acceptance_increment_indicator");
static_assert(offsetof(series_update::fields_type, opening_underlying_market_code) == 59, "unexpected offset of series_update::fields_type::opening_underlying_market_code");
static_assert(offsetof(series_update::fields_type, priority_quote_width) == 60, "unexpected offset of series_update::fields_type::priority_quote_width");
static_assert(offsetof(series_update::fields_type, reserved_8) == 64, "unexpected offset of series_update::fields_type::reserved_8");
static_assert(sizeof(series_update::fields_type) == 72, "unexpected sizeof series_update::fields_type");
static_assert(sizeof(series_update) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 72, "unexpected sizeof series_update");

#pragma pack(pop)
}
