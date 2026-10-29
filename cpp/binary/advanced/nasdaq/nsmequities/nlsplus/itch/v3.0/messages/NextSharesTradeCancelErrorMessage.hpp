#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MarketCenter.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalProxyPrice.hpp"
#include "../types/OriginalNavOffsetAmount.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Next Shares Trade Cancel Error Message
struct next_shares_trade_cancel_error_message {

    struct fields_type {
        itch_nlsplus::market_center market_center;
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::original_trade_control_number original_trade_control_number;
        itch_nlsplus::original_proxy_price original_proxy_price;
        itch_nlsplus::original_nav_offset_amount original_nav_offset_amount;
        itch_nlsplus::original_trade_size original_trade_size;
        itch_nlsplus::original_sale_condition_modifier original_sale_condition_modifier;
        itch_nlsplus::consolidated_volume consolidated_volume;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::next_shares_trade_cancel_error_message};

    fields_type fields;

    // parse method
    static next_shares_trade_cancel_error_message* parse(std::byte* buffer) {
        return reinterpret_cast<next_shares_trade_cancel_error_message*>(buffer);
    }

    // parse method const
    static const next_shares_trade_cancel_error_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const next_shares_trade_cancel_error_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, market_center) == 0, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::market_center");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, issue_symbol) == 1, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::issue_symbol");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, security_class) == 9, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::security_class");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, original_trade_control_number) == 10, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::original_trade_control_number");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, original_proxy_price) == 20, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::original_proxy_price");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, original_nav_offset_amount) == 24, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::original_nav_offset_amount");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, original_trade_size) == 28, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::original_trade_size");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, original_sale_condition_modifier) == 32, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::original_sale_condition_modifier");
static_assert(offsetof(next_shares_trade_cancel_error_message::fields_type, consolidated_volume) == 36, "unexpected offset of next_shares_trade_cancel_error_message::fields_type::consolidated_volume");
static_assert(sizeof(next_shares_trade_cancel_error_message::fields_type) == 44, "unexpected sizeof next_shares_trade_cancel_error_message::fields_type");
static_assert(sizeof(next_shares_trade_cancel_error_message) == sizeof(itch_nlsplus::message_header) + 44, "unexpected sizeof next_shares_trade_cancel_error_message");

#pragma pack(pop)
}
