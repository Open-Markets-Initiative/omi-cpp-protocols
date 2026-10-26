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
#include "../types/BuyerTradeableInstrumentId.hpp"
#include "../types/BuyerSide.hpp"
#include "../types/BuyerOrderId.hpp"
#include "../types/BuyerCombinationTradeId.hpp"
#include "../types/BuyerParticipantId.hpp"
#include "../types/SellerTradeableInstrumentId.hpp"
#include "../types/SellerSide.hpp"
#include "../types/SellerOrderId.hpp"
#include "../types/SellerCombinationTradeId.hpp"
#include "../types/SellerParticipantId.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Combination Trade Executed Message
struct combination_trade_executed_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::trade_type trade_type;
        itch_ntp::trade_id trade_id;
        itch_ntp::executed_quantity executed_quantity;
        itch_ntp::trade_price trade_price;
        itch_ntp::buyer_tradeable_instrument_id buyer_tradeable_instrument_id;
        itch_ntp::buyer_side buyer_side;
        itch_ntp::buyer_order_id buyer_order_id;
        itch_ntp::buyer_combination_trade_id buyer_combination_trade_id;
        itch_ntp::buyer_participant_id buyer_participant_id;
        itch_ntp::seller_tradeable_instrument_id seller_tradeable_instrument_id;
        itch_ntp::seller_side seller_side;
        itch_ntp::seller_order_id seller_order_id;
        itch_ntp::seller_combination_trade_id seller_combination_trade_id;
        itch_ntp::seller_participant_id seller_participant_id;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::combination_trade_executed_message};

    fields_type fields;

    // parse method
    static combination_trade_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<combination_trade_executed_message*>(buffer);
    }

    // parse method const
    static const combination_trade_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const combination_trade_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(combination_trade_executed_message::fields_type, nanoseconds) == 0, "unexpected offset of combination_trade_executed_message::fields_type::nanoseconds");
static_assert(offsetof(combination_trade_executed_message::fields_type, trade_date) == 4, "unexpected offset of combination_trade_executed_message::fields_type::trade_date");
static_assert(offsetof(combination_trade_executed_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of combination_trade_executed_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, trade_type) == 10, "unexpected offset of combination_trade_executed_message::fields_type::trade_type");
static_assert(offsetof(combination_trade_executed_message::fields_type, trade_id) == 11, "unexpected offset of combination_trade_executed_message::fields_type::trade_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, executed_quantity) == 19, "unexpected offset of combination_trade_executed_message::fields_type::executed_quantity");
static_assert(offsetof(combination_trade_executed_message::fields_type, trade_price) == 23, "unexpected offset of combination_trade_executed_message::fields_type::trade_price");
static_assert(offsetof(combination_trade_executed_message::fields_type, buyer_tradeable_instrument_id) == 31, "unexpected offset of combination_trade_executed_message::fields_type::buyer_tradeable_instrument_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, buyer_side) == 35, "unexpected offset of combination_trade_executed_message::fields_type::buyer_side");
static_assert(offsetof(combination_trade_executed_message::fields_type, buyer_order_id) == 36, "unexpected offset of combination_trade_executed_message::fields_type::buyer_order_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, buyer_combination_trade_id) == 44, "unexpected offset of combination_trade_executed_message::fields_type::buyer_combination_trade_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, buyer_participant_id) == 52, "unexpected offset of combination_trade_executed_message::fields_type::buyer_participant_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, seller_tradeable_instrument_id) == 55, "unexpected offset of combination_trade_executed_message::fields_type::seller_tradeable_instrument_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, seller_side) == 59, "unexpected offset of combination_trade_executed_message::fields_type::seller_side");
static_assert(offsetof(combination_trade_executed_message::fields_type, seller_order_id) == 60, "unexpected offset of combination_trade_executed_message::fields_type::seller_order_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, seller_combination_trade_id) == 68, "unexpected offset of combination_trade_executed_message::fields_type::seller_combination_trade_id");
static_assert(offsetof(combination_trade_executed_message::fields_type, seller_participant_id) == 76, "unexpected offset of combination_trade_executed_message::fields_type::seller_participant_id");
static_assert(sizeof(combination_trade_executed_message::fields_type) == 79, "unexpected sizeof combination_trade_executed_message::fields_type");
static_assert(sizeof(combination_trade_executed_message) == sizeof(itch_ntp::message_header) + 79, "unexpected sizeof combination_trade_executed_message");

#pragma pack(pop)
}
