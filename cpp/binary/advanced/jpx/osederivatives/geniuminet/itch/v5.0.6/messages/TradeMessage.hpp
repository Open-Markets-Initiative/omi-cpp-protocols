#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/MatchId.hpp"
#include "../types/ComboGroupId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/TradePrice.hpp"
#include "../types/OwnerParticipantId.hpp"
#include "../types/CounterpartyParticipantId.hpp"
#include "../types/Printable.hpp"
#include "../types/OccurredAtCross.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::match_id match_id;
        itch_geniuminet::combo_group_id combo_group_id;
        itch_geniuminet::side side;
        itch_geniuminet::quantity quantity;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::trade_price trade_price;
        itch_geniuminet::owner_participant_id owner_participant_id;
        itch_geniuminet::counterparty_participant_id counterparty_participant_id;
        itch_geniuminet::printable printable;
        itch_geniuminet::occurred_at_cross occurred_at_cross;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_message};

    fields_type fields;

    // parse method
    static trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_message*>(buffer);
    }

    // parse method const
    static const trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_message::fields_type, nanoseconds) == 0, "unexpected offset of trade_message::fields_type::nanoseconds");
static_assert(offsetof(trade_message::fields_type, match_id) == 4, "unexpected offset of trade_message::fields_type::match_id");
static_assert(offsetof(trade_message::fields_type, combo_group_id) == 12, "unexpected offset of trade_message::fields_type::combo_group_id");
static_assert(offsetof(trade_message::fields_type, side) == 16, "unexpected offset of trade_message::fields_type::side");
static_assert(offsetof(trade_message::fields_type, quantity) == 17, "unexpected offset of trade_message::fields_type::quantity");
static_assert(offsetof(trade_message::fields_type, order_book_id) == 25, "unexpected offset of trade_message::fields_type::order_book_id");
static_assert(offsetof(trade_message::fields_type, trade_price) == 29, "unexpected offset of trade_message::fields_type::trade_price");
static_assert(offsetof(trade_message::fields_type, owner_participant_id) == 33, "unexpected offset of trade_message::fields_type::owner_participant_id");
static_assert(offsetof(trade_message::fields_type, counterparty_participant_id) == 40, "unexpected offset of trade_message::fields_type::counterparty_participant_id");
static_assert(offsetof(trade_message::fields_type, printable) == 47, "unexpected offset of trade_message::fields_type::printable");
static_assert(offsetof(trade_message::fields_type, occurred_at_cross) == 48, "unexpected offset of trade_message::fields_type::occurred_at_cross");
static_assert(sizeof(trade_message::fields_type) == 49, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(itch_geniuminet::message_header) + 49, "unexpected sizeof trade_message");

#pragma pack(pop)
}
