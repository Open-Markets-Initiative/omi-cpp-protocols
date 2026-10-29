#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/OriginatingMarketCenterIdentifier.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/OriginalTradeControlNumber.hpp"
#include "../types/OriginalTradePriceLong.hpp"
#include "../types/OriginalTradeSize.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../types/CorrectedTradeControlNumber.hpp"
#include "../types/CorrectedTradePriceLong.hpp"
#include "../types/CorrectedTradeSize.hpp"
#include "../structs/CorrectedSaleConditionModifier.hpp"
#include "../types/ConsolidatedVolume.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Long Form Trade Correction Message
struct long_form_trade_correction_message {

    struct fields_type {
        itch_nlsplus::originating_market_center_identifier originating_market_center_identifier;
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::original_trade_control_number original_trade_control_number;
        itch_nlsplus::original_trade_price_long original_trade_price_long;
        itch_nlsplus::original_trade_size original_trade_size;
        itch_nlsplus::original_sale_condition_modifier original_sale_condition_modifier;
        itch_nlsplus::corrected_trade_control_number corrected_trade_control_number;
        itch_nlsplus::corrected_trade_price_long corrected_trade_price_long;
        itch_nlsplus::corrected_trade_size corrected_trade_size;
        itch_nlsplus::corrected_sale_condition_modifier corrected_sale_condition_modifier;
        itch_nlsplus::consolidated_volume consolidated_volume;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::long_form_trade_correction_message};

    fields_type fields;

    // parse method
    static long_form_trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_form_trade_correction_message*>(buffer);
    }

    // parse method const
    static const long_form_trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_form_trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_form_trade_correction_message::fields_type, originating_market_center_identifier) == 0, "unexpected offset of long_form_trade_correction_message::fields_type::originating_market_center_identifier");
static_assert(offsetof(long_form_trade_correction_message::fields_type, issue_symbol) == 1, "unexpected offset of long_form_trade_correction_message::fields_type::issue_symbol");
static_assert(offsetof(long_form_trade_correction_message::fields_type, security_class) == 9, "unexpected offset of long_form_trade_correction_message::fields_type::security_class");
static_assert(offsetof(long_form_trade_correction_message::fields_type, original_trade_control_number) == 10, "unexpected offset of long_form_trade_correction_message::fields_type::original_trade_control_number");
static_assert(offsetof(long_form_trade_correction_message::fields_type, original_trade_price_long) == 20, "unexpected offset of long_form_trade_correction_message::fields_type::original_trade_price_long");
static_assert(offsetof(long_form_trade_correction_message::fields_type, original_trade_size) == 28, "unexpected offset of long_form_trade_correction_message::fields_type::original_trade_size");
static_assert(offsetof(long_form_trade_correction_message::fields_type, original_sale_condition_modifier) == 32, "unexpected offset of long_form_trade_correction_message::fields_type::original_sale_condition_modifier");
static_assert(offsetof(long_form_trade_correction_message::fields_type, corrected_trade_control_number) == 36, "unexpected offset of long_form_trade_correction_message::fields_type::corrected_trade_control_number");
static_assert(offsetof(long_form_trade_correction_message::fields_type, corrected_trade_price_long) == 46, "unexpected offset of long_form_trade_correction_message::fields_type::corrected_trade_price_long");
static_assert(offsetof(long_form_trade_correction_message::fields_type, corrected_trade_size) == 54, "unexpected offset of long_form_trade_correction_message::fields_type::corrected_trade_size");
static_assert(offsetof(long_form_trade_correction_message::fields_type, corrected_sale_condition_modifier) == 58, "unexpected offset of long_form_trade_correction_message::fields_type::corrected_sale_condition_modifier");
static_assert(offsetof(long_form_trade_correction_message::fields_type, consolidated_volume) == 62, "unexpected offset of long_form_trade_correction_message::fields_type::consolidated_volume");
static_assert(sizeof(long_form_trade_correction_message::fields_type) == 70, "unexpected sizeof long_form_trade_correction_message::fields_type");
static_assert(sizeof(long_form_trade_correction_message) == sizeof(itch_nlsplus::message_header) + 70, "unexpected sizeof long_form_trade_correction_message");

#pragma pack(pop)
}
