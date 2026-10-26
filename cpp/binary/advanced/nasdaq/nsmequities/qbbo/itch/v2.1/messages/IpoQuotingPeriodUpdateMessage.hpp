#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Tracking.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/IpoQuotationReleaseTime.hpp"
#include "../types/IpoQuotationReleaseQualifier.hpp"
#include "../types/IpoPrice.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Ipo Quoting Period Update Message
struct ipo_quoting_period_update_message {

    struct fields_type {
        itch_qbbo::tracking tracking;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::stock stock;
        itch_qbbo::ipo_quotation_release_time ipo_quotation_release_time;
        itch_qbbo::ipo_quotation_release_qualifier ipo_quotation_release_qualifier;
        itch_qbbo::ipo_price ipo_price;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::ipo_quoting_period_update_message};

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
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, tracking) == 0, "unexpected offset of ipo_quoting_period_update_message::fields_type::tracking");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, time_stamp) == 2, "unexpected offset of ipo_quoting_period_update_message::fields_type::time_stamp");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, stock) == 8, "unexpected offset of ipo_quoting_period_update_message::fields_type::stock");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_quotation_release_time) == 16, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_quotation_release_time");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_quotation_release_qualifier) == 20, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_quotation_release_qualifier");
static_assert(offsetof(ipo_quoting_period_update_message::fields_type, ipo_price) == 21, "unexpected offset of ipo_quoting_period_update_message::fields_type::ipo_price");
static_assert(sizeof(ipo_quoting_period_update_message::fields_type) == 25, "unexpected sizeof ipo_quoting_period_update_message::fields_type");
static_assert(sizeof(ipo_quoting_period_update_message) == sizeof(itch_qbbo::message_header) + 25, "unexpected sizeof ipo_quoting_period_update_message");

#pragma pack(pop)
}
