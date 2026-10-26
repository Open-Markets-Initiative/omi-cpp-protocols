#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/TradeType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/TradePrice.hpp"
#include "../types/CombinationTradeId.hpp"
#include "../types/ParticipantIdBuyer.hpp"
#include "../types/ParticipantIdSeller.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Trade Executed Message
struct trade_executed_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::trade_type trade_type;
        itch_ntp::trade_id trade_id;
        itch_ntp::executed_quantity executed_quantity;
        itch_ntp::trade_price trade_price;
        itch_ntp::combination_trade_id combination_trade_id;
        itch_ntp::participant_id_buyer participant_id_buyer;
        itch_ntp::participant_id_seller participant_id_seller;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_executed_message};

    fields_type fields;

    // parse method
    static trade_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_executed_message*>(buffer);
    }

    // parse method const
    static const trade_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_executed_message::fields_type, nanoseconds) == 0, "unexpected offset of trade_executed_message::fields_type::nanoseconds");
static_assert(offsetof(trade_executed_message::fields_type, trade_date) == 4, "unexpected offset of trade_executed_message::fields_type::trade_date");
static_assert(offsetof(trade_executed_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of trade_executed_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(trade_executed_message::fields_type, trade_type) == 10, "unexpected offset of trade_executed_message::fields_type::trade_type");
static_assert(offsetof(trade_executed_message::fields_type, trade_id) == 11, "unexpected offset of trade_executed_message::fields_type::trade_id");
static_assert(offsetof(trade_executed_message::fields_type, executed_quantity) == 19, "unexpected offset of trade_executed_message::fields_type::executed_quantity");
static_assert(offsetof(trade_executed_message::fields_type, trade_price) == 23, "unexpected offset of trade_executed_message::fields_type::trade_price");
static_assert(offsetof(trade_executed_message::fields_type, combination_trade_id) == 31, "unexpected offset of trade_executed_message::fields_type::combination_trade_id");
static_assert(offsetof(trade_executed_message::fields_type, participant_id_buyer) == 39, "unexpected offset of trade_executed_message::fields_type::participant_id_buyer");
static_assert(offsetof(trade_executed_message::fields_type, participant_id_seller) == 42, "unexpected offset of trade_executed_message::fields_type::participant_id_seller");
static_assert(sizeof(trade_executed_message::fields_type) == 45, "unexpected sizeof trade_executed_message::fields_type");
static_assert(sizeof(trade_executed_message) == sizeof(itch_ntp::message_header) + 45, "unexpected sizeof trade_executed_message");

#pragma pack(pop)
}
