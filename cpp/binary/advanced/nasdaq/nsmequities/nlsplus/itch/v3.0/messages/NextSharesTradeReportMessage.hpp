#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/NextSharesSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/TradeControlNumber.hpp"
#include "../types/ProxyPrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/NavOffsetAmount.hpp"
#include "../structs/SaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Next Shares Trade Report Message
struct next_shares_trade_report_message {

    struct fields_type {
        itch_nlsplus::originating_market_center_identifier originating_market_center_identifier;
        itch_nlsplus::next_shares_symbol next_shares_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::trade_control_number trade_control_number;
        itch_nlsplus::proxy_price proxy_price;
        itch_nlsplus::trade_size trade_size;
        itch_nlsplus::nav_offset_amount nav_offset_amount;
        itch_nlsplus::sale_condition_modifier sale_condition_modifier;
        itch_nlsplus::consolidated_volume consolidated_volume;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::next_shares_trade_report_message};

    fields_type fields;

    // parse method
    static next_shares_trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<next_shares_trade_report_message*>(buffer);
    }

    // parse method const
    static const next_shares_trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const next_shares_trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(next_shares_trade_report_message::fields_type, originating_market_center_identifier) == 0, "unexpected offset of next_shares_trade_report_message::fields_type::originating_market_center_identifier");
static_assert(offsetof(next_shares_trade_report_message::fields_type, next_shares_symbol) == 1, "unexpected offset of next_shares_trade_report_message::fields_type::next_shares_symbol");
static_assert(offsetof(next_shares_trade_report_message::fields_type, security_class) == 9, "unexpected offset of next_shares_trade_report_message::fields_type::security_class");
static_assert(offsetof(next_shares_trade_report_message::fields_type, trade_control_number) == 10, "unexpected offset of next_shares_trade_report_message::fields_type::trade_control_number");
static_assert(offsetof(next_shares_trade_report_message::fields_type, proxy_price) == 20, "unexpected offset of next_shares_trade_report_message::fields_type::proxy_price");
static_assert(offsetof(next_shares_trade_report_message::fields_type, trade_size) == 24, "unexpected offset of next_shares_trade_report_message::fields_type::trade_size");
static_assert(offsetof(next_shares_trade_report_message::fields_type, nav_offset_amount) == 28, "unexpected offset of next_shares_trade_report_message::fields_type::nav_offset_amount");
static_assert(offsetof(next_shares_trade_report_message::fields_type, sale_condition_modifier) == 32, "unexpected offset of next_shares_trade_report_message::fields_type::sale_condition_modifier");
static_assert(offsetof(next_shares_trade_report_message::fields_type, consolidated_volume) == 36, "unexpected offset of next_shares_trade_report_message::fields_type::consolidated_volume");
static_assert(sizeof(next_shares_trade_report_message::fields_type) == 44, "unexpected sizeof next_shares_trade_report_message::fields_type");
static_assert(sizeof(next_shares_trade_report_message) == sizeof(itch_nlsplus::message_header) + 44, "unexpected sizeof next_shares_trade_report_message");

#pragma pack(pop)
}
