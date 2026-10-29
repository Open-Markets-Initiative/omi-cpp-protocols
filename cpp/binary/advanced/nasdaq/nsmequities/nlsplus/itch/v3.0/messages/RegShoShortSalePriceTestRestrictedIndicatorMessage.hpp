#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/RegShoAction.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Reg Sho Short Sale Price Test Restricted Indicator Message
struct reg_sho_short_sale_price_test_restricted_indicator_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::reg_sho_action reg_sho_action;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::reg_sho_short_sale_price_test_restricted_indicator_message};

    fields_type fields;

    // parse method
    static reg_sho_short_sale_price_test_restricted_indicator_message* parse(std::byte* buffer) {
        return reinterpret_cast<reg_sho_short_sale_price_test_restricted_indicator_message*>(buffer);
    }

    // parse method const
    static const reg_sho_short_sale_price_test_restricted_indicator_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reg_sho_short_sale_price_test_restricted_indicator_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reg_sho_short_sale_price_test_restricted_indicator_message::fields_type, issue_symbol) == 0, "unexpected offset of reg_sho_short_sale_price_test_restricted_indicator_message::fields_type::issue_symbol");
static_assert(offsetof(reg_sho_short_sale_price_test_restricted_indicator_message::fields_type, reg_sho_action) == 8, "unexpected offset of reg_sho_short_sale_price_test_restricted_indicator_message::fields_type::reg_sho_action");
static_assert(sizeof(reg_sho_short_sale_price_test_restricted_indicator_message::fields_type) == 9, "unexpected sizeof reg_sho_short_sale_price_test_restricted_indicator_message::fields_type");
static_assert(sizeof(reg_sho_short_sale_price_test_restricted_indicator_message) == sizeof(itch_nlsplus::message_header) + 9, "unexpected sizeof reg_sho_short_sale_price_test_restricted_indicator_message");

#pragma pack(pop)
}
