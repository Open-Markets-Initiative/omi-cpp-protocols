#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/Mpid.hpp"
#include "../types/Stock.hpp"
#include "../types/PrimaryMarketMaker.hpp"
#include "../types/MarketMakerMode.hpp"
#include "../types/MarketParticipantState.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Market Participant Position Message
struct market_participant_position_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::mpid mpid;
        itch_totalview::stock stock;
        itch_totalview::primary_market_maker primary_market_maker;
        itch_totalview::market_maker_mode market_maker_mode;
        itch_totalview::market_participant_state market_participant_state;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::market_participant_position_message};

    fields_type fields;

    // parse method
    static market_participant_position_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_participant_position_message*>(buffer);
    }

    // parse method const
    static const market_participant_position_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_participant_position_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_participant_position_message::fields_type, nanoseconds) == 0, "unexpected offset of market_participant_position_message::fields_type::nanoseconds");
static_assert(offsetof(market_participant_position_message::fields_type, mpid) == 4, "unexpected offset of market_participant_position_message::fields_type::mpid");
static_assert(offsetof(market_participant_position_message::fields_type, stock) == 8, "unexpected offset of market_participant_position_message::fields_type::stock");
static_assert(offsetof(market_participant_position_message::fields_type, primary_market_maker) == 14, "unexpected offset of market_participant_position_message::fields_type::primary_market_maker");
static_assert(offsetof(market_participant_position_message::fields_type, market_maker_mode) == 15, "unexpected offset of market_participant_position_message::fields_type::market_maker_mode");
static_assert(offsetof(market_participant_position_message::fields_type, market_participant_state) == 16, "unexpected offset of market_participant_position_message::fields_type::market_participant_state");
static_assert(sizeof(market_participant_position_message::fields_type) == 17, "unexpected sizeof market_participant_position_message::fields_type");
static_assert(sizeof(market_participant_position_message) == sizeof(itch_totalview::message_header) + 17, "unexpected sizeof market_participant_position_message");

#pragma pack(pop)
}
