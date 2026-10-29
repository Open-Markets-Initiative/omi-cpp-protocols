#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Symbol.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/OriginalExecutionId.hpp"
#include "../types/OriginalTradePrice.hpp"
#include "../types/OriginalTradeQuantity.hpp"
#include "../types/CorrectedTradePrice.hpp"
#include "../types/CorrectedTradeQuantity.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Trade Correct Message
struct trade_correct_message {

    struct fields_type {
        aspen_marketdatafeed::symbol_id symbol_id;
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::reserved_8 reserved_8;
        aspen_marketdatafeed::reserved_1 reserved_1;
        aspen_marketdatafeed::symbol symbol;
        aspen_marketdatafeed::execution_id execution_id;
        aspen_marketdatafeed::broker broker;
        aspen_marketdatafeed::contra_broker contra_broker;
        aspen_marketdatafeed::original_execution_id original_execution_id;
        aspen_marketdatafeed::original_trade_price original_trade_price;
        aspen_marketdatafeed::original_trade_quantity original_trade_quantity;
        aspen_marketdatafeed::corrected_trade_price corrected_trade_price;
        aspen_marketdatafeed::corrected_trade_quantity corrected_trade_quantity;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_correct_message};

    fields_type fields;

    // parse method
    static trade_correct_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_correct_message*>(buffer);
    }

    // parse method const
    static const trade_correct_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_correct_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_correct_message::fields_type, symbol_id) == 0, "unexpected offset of trade_correct_message::fields_type::symbol_id");
static_assert(offsetof(trade_correct_message::fields_type, timestamp) == 2, "unexpected offset of trade_correct_message::fields_type::timestamp");
static_assert(offsetof(trade_correct_message::fields_type, reserved_8) == 10, "unexpected offset of trade_correct_message::fields_type::reserved_8");
static_assert(offsetof(trade_correct_message::fields_type, reserved_1) == 18, "unexpected offset of trade_correct_message::fields_type::reserved_1");
static_assert(offsetof(trade_correct_message::fields_type, symbol) == 19, "unexpected offset of trade_correct_message::fields_type::symbol");
static_assert(offsetof(trade_correct_message::fields_type, execution_id) == 30, "unexpected offset of trade_correct_message::fields_type::execution_id");
static_assert(offsetof(trade_correct_message::fields_type, broker) == 38, "unexpected offset of trade_correct_message::fields_type::broker");
static_assert(offsetof(trade_correct_message::fields_type, contra_broker) == 41, "unexpected offset of trade_correct_message::fields_type::contra_broker");
static_assert(offsetof(trade_correct_message::fields_type, original_execution_id) == 44, "unexpected offset of trade_correct_message::fields_type::original_execution_id");
static_assert(offsetof(trade_correct_message::fields_type, original_trade_price) == 52, "unexpected offset of trade_correct_message::fields_type::original_trade_price");
static_assert(offsetof(trade_correct_message::fields_type, original_trade_quantity) == 60, "unexpected offset of trade_correct_message::fields_type::original_trade_quantity");
static_assert(offsetof(trade_correct_message::fields_type, corrected_trade_price) == 68, "unexpected offset of trade_correct_message::fields_type::corrected_trade_price");
static_assert(offsetof(trade_correct_message::fields_type, corrected_trade_quantity) == 76, "unexpected offset of trade_correct_message::fields_type::corrected_trade_quantity");
static_assert(sizeof(trade_correct_message::fields_type) == 84, "unexpected sizeof trade_correct_message::fields_type");
static_assert(sizeof(trade_correct_message) == sizeof(aspen_marketdatafeed::message_header) + 84, "unexpected sizeof trade_correct_message");

#pragma pack(pop)
}
