#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/CorrectedTradeControlNumber.hpp"
#include "../types/CorrectedTradePrice.hpp"
#include "../types/CorrectedTradeSize.hpp"
#include "../structs/CorrectedSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Trade Correction Message
struct trade_correction_message {

    struct fields_type {
        itch_nlsplus::originating_market_center_identifier originating_market_center_identifier;
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::original_trade_control_number original_trade_control_number;
        itch_nlsplus::original_trade_price original_trade_price;
        itch_nlsplus::original_trade_size original_trade_size;
        itch_nlsplus::original_sale_condition_modifier original_sale_condition_modifier;
        itch_nlsplus::corrected_trade_control_number corrected_trade_control_number;
        itch_nlsplus::corrected_trade_price corrected_trade_price;
        itch_nlsplus::corrected_trade_size corrected_trade_size;
        itch_nlsplus::corrected_sale_condition_modifier corrected_sale_condition_modifier;
        itch_nlsplus::consolidated_volume consolidated_volume;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::trade_correction_message};

    fields_type fields;

    // parse method
    static trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_correction_message*>(buffer);
    }

    // parse method const
    static const trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_correction_message::fields_type, originating_market_center_identifier) == 0, "unexpected offset of trade_correction_message::fields_type::originating_market_center_identifier");
static_assert(offsetof(trade_correction_message::fields_type, issue_symbol) == 1, "unexpected offset of trade_correction_message::fields_type::issue_symbol");
static_assert(offsetof(trade_correction_message::fields_type, security_class) == 9, "unexpected offset of trade_correction_message::fields_type::security_class");
static_assert(offsetof(trade_correction_message::fields_type, original_trade_control_number) == 10, "unexpected offset of trade_correction_message::fields_type::original_trade_control_number");
static_assert(offsetof(trade_correction_message::fields_type, original_trade_price) == 20, "unexpected offset of trade_correction_message::fields_type::original_trade_price");
static_assert(offsetof(trade_correction_message::fields_type, original_trade_size) == 24, "unexpected offset of trade_correction_message::fields_type::original_trade_size");
static_assert(offsetof(trade_correction_message::fields_type, original_sale_condition_modifier) == 28, "unexpected offset of trade_correction_message::fields_type::original_sale_condition_modifier");
static_assert(offsetof(trade_correction_message::fields_type, corrected_trade_control_number) == 32, "unexpected offset of trade_correction_message::fields_type::corrected_trade_control_number");
static_assert(offsetof(trade_correction_message::fields_type, corrected_trade_price) == 42, "unexpected offset of trade_correction_message::fields_type::corrected_trade_price");
static_assert(offsetof(trade_correction_message::fields_type, corrected_trade_size) == 46, "unexpected offset of trade_correction_message::fields_type::corrected_trade_size");
static_assert(offsetof(trade_correction_message::fields_type, corrected_sale_condition_modifier) == 50, "unexpected offset of trade_correction_message::fields_type::corrected_sale_condition_modifier");
static_assert(offsetof(trade_correction_message::fields_type, consolidated_volume) == 54, "unexpected offset of trade_correction_message::fields_type::consolidated_volume");
static_assert(sizeof(trade_correction_message::fields_type) == 62, "unexpected sizeof trade_correction_message::fields_type");
static_assert(sizeof(trade_correction_message) == sizeof(itch_nlsplus::message_header) + 62, "unexpected sizeof trade_correction_message");

#pragma pack(pop)
}
