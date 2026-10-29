#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/AdjustedClosingPrice.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Adjusted Closing Price Message
struct adjusted_closing_price_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::adjusted_closing_price adjusted_closing_price;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::adjusted_closing_price_message};

    fields_type fields;

    // parse method
    static adjusted_closing_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<adjusted_closing_price_message*>(buffer);
    }

    // parse method const
    static const adjusted_closing_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const adjusted_closing_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(adjusted_closing_price_message::fields_type, issue_symbol) == 0, "unexpected offset of adjusted_closing_price_message::fields_type::issue_symbol");
static_assert(offsetof(adjusted_closing_price_message::fields_type, security_class) == 8, "unexpected offset of adjusted_closing_price_message::fields_type::security_class");
static_assert(offsetof(adjusted_closing_price_message::fields_type, adjusted_closing_price) == 9, "unexpected offset of adjusted_closing_price_message::fields_type::adjusted_closing_price");
static_assert(sizeof(adjusted_closing_price_message::fields_type) == 13, "unexpected sizeof adjusted_closing_price_message::fields_type");
static_assert(sizeof(adjusted_closing_price_message) == sizeof(itch_nlsplus::message_header) + 13, "unexpected sizeof adjusted_closing_price_message");

#pragma pack(pop)
}
