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
#include "../types/OwnerParticipantId.hpp"
#include "../types/CounterpartyParticipantId.hpp"
#include "../types/TradePrice.hpp"
#include "../types/OccurredAtCross.hpp"
#include "../types/Printable.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Order Executed With Price Message
struct order_executed_with_price_message {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_id order_id;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::side side;
        itch_geniuminet::executed_quantity executed_quantity;
        itch_geniuminet::match_id match_id;
        itch_geniuminet::combo_group_id combo_group_id;
        itch_geniuminet::owner_participant_id owner_participant_id;
        itch_geniuminet::counterparty_participant_id counterparty_participant_id;
        itch_geniuminet::trade_price trade_price;
        itch_geniuminet::occurred_at_cross occurred_at_cross;
        itch_geniuminet::printable printable;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_with_price_message};

    fields_type fields;

    // parse method
    static order_executed_with_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_with_price_message*>(buffer);
    }

    // parse method const
    static const order_executed_with_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_with_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_with_price_message::fields_type, nanoseconds) == 0, "unexpected offset of order_executed_with_price_message::fields_type::nanoseconds");
static_assert(offsetof(order_executed_with_price_message::fields_type, order_id) == 4, "unexpected offset of order_executed_with_price_message::fields_type::order_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, order_book_id) == 12, "unexpected offset of order_executed_with_price_message::fields_type::order_book_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, side) == 16, "unexpected offset of order_executed_with_price_message::fields_type::side");
static_assert(offsetof(order_executed_with_price_message::fields_type, executed_quantity) == 17, "unexpected offset of order_executed_with_price_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_with_price_message::fields_type, match_id) == 25, "unexpected offset of order_executed_with_price_message::fields_type::match_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, combo_group_id) == 33, "unexpected offset of order_executed_with_price_message::fields_type::combo_group_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, owner_participant_id) == 37, "unexpected offset of order_executed_with_price_message::fields_type::owner_participant_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, counterparty_participant_id) == 44, "unexpected offset of order_executed_with_price_message::fields_type::counterparty_participant_id");
static_assert(offsetof(order_executed_with_price_message::fields_type, trade_price) == 51, "unexpected offset of order_executed_with_price_message::fields_type::trade_price");
static_assert(offsetof(order_executed_with_price_message::fields_type, occurred_at_cross) == 55, "unexpected offset of order_executed_with_price_message::fields_type::occurred_at_cross");
static_assert(offsetof(order_executed_with_price_message::fields_type, printable) == 56, "unexpected offset of order_executed_with_price_message::fields_type::printable");
static_assert(sizeof(order_executed_with_price_message::fields_type) == 57, "unexpected sizeof order_executed_with_price_message::fields_type");
static_assert(sizeof(order_executed_with_price_message) == sizeof(itch_geniuminet::message_header) + 57, "unexpected sizeof order_executed_with_price_message");

#pragma pack(pop)
}
