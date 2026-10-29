#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/AdjustedClosingPriceLong.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Long Form Adjusted Closing Price Message
struct long_form_adjusted_closing_price_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::adjusted_closing_price_long adjusted_closing_price_long;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::long_form_adjusted_closing_price_message};

    fields_type fields;

    // parse method
    static long_form_adjusted_closing_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_form_adjusted_closing_price_message*>(buffer);
    }

    // parse method const
    static const long_form_adjusted_closing_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_form_adjusted_closing_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_form_adjusted_closing_price_message::fields_type, issue_symbol) == 0, "unexpected offset of long_form_adjusted_closing_price_message::fields_type::issue_symbol");
static_assert(offsetof(long_form_adjusted_closing_price_message::fields_type, security_class) == 8, "unexpected offset of long_form_adjusted_closing_price_message::fields_type::security_class");
static_assert(offsetof(long_form_adjusted_closing_price_message::fields_type, adjusted_closing_price_long) == 9, "unexpected offset of long_form_adjusted_closing_price_message::fields_type::adjusted_closing_price_long");
static_assert(sizeof(long_form_adjusted_closing_price_message::fields_type) == 17, "unexpected sizeof long_form_adjusted_closing_price_message::fields_type");
static_assert(sizeof(long_form_adjusted_closing_price_message) == sizeof(itch_nlsplus::message_header) + 17, "unexpected sizeof long_form_adjusted_closing_price_message");

#pragma pack(pop)
}
