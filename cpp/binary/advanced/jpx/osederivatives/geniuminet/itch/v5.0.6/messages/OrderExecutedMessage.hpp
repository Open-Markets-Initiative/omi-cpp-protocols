#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchId.hpp"
#include "../types/ComboGroupId.hpp"
#include "../types/ParticipantIdOwner.hpp"
#include "../types/ParticipantIdCounterparty.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_id order_id;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::side side;
        itch_geniuminet::executed_quantity executed_quantity;
        itch_geniuminet::match_id match_id;
        itch_geniuminet::combo_group_id combo_group_id;
        itch_geniuminet::participant_id_owner participant_id_owner;
        itch_geniuminet::participant_id_counterparty participant_id_counterparty;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_message};

    fields_type fields;

    // parse method
    static order_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_message*>(buffer);
    }

    // parse method const
    static const order_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_message::fields_type, nanoseconds) == 0, "unexpected offset of order_executed_message::fields_type::nanoseconds");
static_assert(offsetof(order_executed_message::fields_type, order_id) == 4, "unexpected offset of order_executed_message::fields_type::order_id");
static_assert(offsetof(order_executed_message::fields_type, order_book_id) == 12, "unexpected offset of order_executed_message::fields_type::order_book_id");
static_assert(offsetof(order_executed_message::fields_type, side) == 16, "unexpected offset of order_executed_message::fields_type::side");
static_assert(offsetof(order_executed_message::fields_type, executed_quantity) == 17, "unexpected offset of order_executed_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_message::fields_type, match_id) == 25, "unexpected offset of order_executed_message::fields_type::match_id");
static_assert(offsetof(order_executed_message::fields_type, combo_group_id) == 33, "unexpected offset of order_executed_message::fields_type::combo_group_id");
static_assert(offsetof(order_executed_message::fields_type, participant_id_owner) == 37, "unexpected offset of order_executed_message::fields_type::participant_id_owner");
static_assert(offsetof(order_executed_message::fields_type, participant_id_counterparty) == 44, "unexpected offset of order_executed_message::fields_type::participant_id_counterparty");
static_assert(sizeof(order_executed_message::fields_type) == 51, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(itch_geniuminet::message_header) + 51, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
