#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Tracking.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/InterestFlag.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

#pragma pack(push, 1)

// Price Improvement Message
struct price_improvement_message {

    struct fields_type {
        itch_qbbo::tracking tracking;
        itch_qbbo::time_stamp time_stamp;
        itch_qbbo::stock stock;
        itch_qbbo::interest_flag interest_flag;
    };

    itch_qbbo::message_header header = {std::uint16_t(sizeof(itch_qbbo::message_header) + sizeof(fields_type) - 2), message_type::enum_type::price_improvement_message};

    fields_type fields;

    // parse method
    static price_improvement_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_improvement_message*>(buffer);
    }

    // parse method const
    static const price_improvement_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_improvement_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_improvement_message::fields_type, tracking) == 0, "unexpected offset of price_improvement_message::fields_type::tracking");
static_assert(offsetof(price_improvement_message::fields_type, time_stamp) == 2, "unexpected offset of price_improvement_message::fields_type::time_stamp");
static_assert(offsetof(price_improvement_message::fields_type, stock) == 8, "unexpected offset of price_improvement_message::fields_type::stock");
static_assert(offsetof(price_improvement_message::fields_type, interest_flag) == 16, "unexpected offset of price_improvement_message::fields_type::interest_flag");
static_assert(sizeof(price_improvement_message::fields_type) == 17, "unexpected sizeof price_improvement_message::fields_type");
static_assert(sizeof(price_improvement_message) == sizeof(itch_qbbo::message_header) + 17, "unexpected sizeof price_improvement_message");

#pragma pack(pop)
}
