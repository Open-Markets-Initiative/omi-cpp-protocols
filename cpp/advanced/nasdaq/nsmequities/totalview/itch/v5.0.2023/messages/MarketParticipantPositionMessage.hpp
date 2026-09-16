#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Mpid.hpp"
#include "../types/Stock.hpp"
#include "../types/PrimaryMarketMaker.hpp"
#include "../types/MarketMakerMode.hpp"
#include "../types/MarketParticipantState.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Market Participant Position Message
struct market_participant_position_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
        itch_totalview::mpid mpid;
        itch_totalview::stock stock;
        itch_totalview::primary_market_maker primary_market_maker;
        itch_totalview::market_maker_mode market_maker_mode;
        itch_totalview::market_participant_state market_participant_state;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::market_participant_position_message};

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
static_assert(offsetof(market_participant_position_message::fields_type, stock_locate) == 0, "unexpected offset of market_participant_position_message::fields_type::stock_locate");
static_assert(offsetof(market_participant_position_message::fields_type, tracking_number) == 2, "unexpected offset of market_participant_position_message::fields_type::tracking_number");
static_assert(offsetof(market_participant_position_message::fields_type, timestamp) == 4, "unexpected offset of market_participant_position_message::fields_type::timestamp");
static_assert(offsetof(market_participant_position_message::fields_type, mpid) == 10, "unexpected offset of market_participant_position_message::fields_type::mpid");
static_assert(offsetof(market_participant_position_message::fields_type, stock) == 14, "unexpected offset of market_participant_position_message::fields_type::stock");
static_assert(offsetof(market_participant_position_message::fields_type, primary_market_maker) == 22, "unexpected offset of market_participant_position_message::fields_type::primary_market_maker");
static_assert(offsetof(market_participant_position_message::fields_type, market_maker_mode) == 23, "unexpected offset of market_participant_position_message::fields_type::market_maker_mode");
static_assert(offsetof(market_participant_position_message::fields_type, market_participant_state) == 24, "unexpected offset of market_participant_position_message::fields_type::market_participant_state");
static_assert(sizeof(market_participant_position_message::fields_type) == 25, "unexpected sizeof market_participant_position_message::fields_type");
static_assert(sizeof(market_participant_position_message) == sizeof(message_header) + 25, "unexpected sizeof market_participant_position_message");

#pragma pack(pop)
}
