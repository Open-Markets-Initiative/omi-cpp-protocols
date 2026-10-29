#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Stock.hpp"
#include "../types/IpoQuotationReleaseTime.hpp"
#include "../types/IpoQuotationReleaseQualifier.hpp"
#include "../types/IpoPrice.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Ipo Quoting Period Update Message
struct ipo_quoting_period_update_message {

    struct fields_type {
        itch_nlsplus::stock stock;
        itch_nlsplus::ipo_quotation_release_time ipo_quotation_release_time;
        itch_nlsplus::ipo_quotation_release_qualifier ipo_quotation_release_qualifier;
        itch_nlsplus::ipo_price ipo_price;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::ipo_quoting_period_update_message};

    fields_type fields;

    // parse method
    static ipo_quoting_period_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<ipo_quoting_period_update_message*>(buffer);
    }

    // parse method const
    static const ipo_quoting_period_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ipo_quoting_period_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, stock) == 0, "unexpected offset of ipo_quoting_period_update_message::fields_type::stock");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_quotation_release_time) == 8, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_quotation_release_time");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_quotation_release_qualifier) == 12, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_quotation_release_qualifier");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_price) == 13, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_price");
static_assert(sizeof(ipo_quoting_period_update_message::fields_type) == 17, "unexpected sizeof ipo_quoting_period_update_message::fields_type");
static_assert(sizeof(ipo_quoting_period_update_message) == sizeof(itch_nlsplus::message_header) + 17, "unexpected sizeof ipo_quoting_period_update_message");

#pragma pack(pop)
}
