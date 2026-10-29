#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/TradeControlNumber.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../structs/SaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Trade Report Message
struct trade_report_message {

    struct fields_type {
        itch_nlsplus::originating_market_center_identifier originating_market_center_identifier;
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::trade_control_number trade_control_number;
        itch_nlsplus::trade_price trade_price;
        itch_nlsplus::trade_size trade_size;
        itch_nlsplus::sale_condition_modifier sale_condition_modifier;
        itch_nlsplus::consolidated_volume consolidated_volume;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::trade_report_message};

    fields_type fields;

    // parse method
    static trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report_message*>(buffer);
    }

    // parse method const
    static const trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report_message::fields_type, originating_market_center_identifier) == 0, "unexpected offset of trade_report_message::fields_type::originating_market_center_identifier");
static_assert(offsetof(trade_report_message::fields_type, issue_symbol) == 1, "unexpected offset of trade_report_message::fields_type::issue_symbol");
static_assert(offsetof(trade_report_message::fields_type, security_class) == 9, "unexpected offset of trade_report_message::fields_type::security_class");
static_assert(offsetof(trade_report_message::fields_type, trade_control_number) == 10, "unexpected offset of trade_report_message::fields_type::trade_control_number");
static_assert(offsetof(trade_report_message::fields_type, trade_price) == 20, "unexpected offset of trade_report_message::fields_type::trade_price");
static_assert(offsetof(trade_report_message::fields_type, trade_size) == 24, "unexpected offset of trade_report_message::fields_type::trade_size");
static_assert(offsetof(trade_report_message::fields_type, sale_condition_modifier) == 28, "unexpected offset of trade_report_message::fields_type::sale_condition_modifier");
static_assert(offsetof(trade_report_message::fields_type, consolidated_volume) == 32, "unexpected offset of trade_report_message::fields_type::consolidated_volume");
static_assert(sizeof(trade_report_message::fields_type) == 40, "unexpected sizeof trade_report_message::fields_type");
static_assert(sizeof(trade_report_message) == sizeof(itch_nlsplus::message_header) + 40, "unexpected sizeof trade_report_message");

#pragma pack(pop)
}
