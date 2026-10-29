#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/ReferenceForNetChange.hpp"
#include "../types/ReferencePrice.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Ipo Information Message
struct ipo_information_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::security_class security_class;
        itch_nlsplus::reference_for_net_change reference_for_net_change;
        itch_nlsplus::reference_price reference_price;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::ipo_information_message};

    fields_type fields;

    // parse method
    static ipo_information_message* parse(std::byte* buffer) {
        return reinterpret_cast<ipo_information_message*>(buffer);
    }

    // parse method const
    static const ipo_information_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ipo_information_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(ipo_information_message::fields_type, issue_symbol) == 0, "unexpected offset of ipo_information_message::fields_type::issue_symbol");
static_assert(offsetof(ipo_information_message::fields_type, security_class) == 8, "unexpected offset of ipo_information_message::fields_type::security_class");
static_assert(offsetof(ipo_information_message::fields_type, reference_for_net_change) == 9, "unexpected offset of ipo_information_message::fields_type::reference_for_net_change");
static_assert(offsetof(ipo_information_message::fields_type, reference_price) == 10, "unexpected offset of ipo_information_message::fields_type::reference_price");
static_assert(sizeof(ipo_information_message::fields_type) == 14, "unexpected sizeof ipo_information_message::fields_type");
static_assert(sizeof(ipo_information_message) == sizeof(itch_nlsplus::message_header) + 14, "unexpected sizeof ipo_information_message");

#pragma pack(pop)
}
