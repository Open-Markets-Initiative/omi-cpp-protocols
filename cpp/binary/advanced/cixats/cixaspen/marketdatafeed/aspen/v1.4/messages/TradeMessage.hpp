#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Symbol.hpp"
#include "../types/Price.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Broker.hpp"
#include "../types/ContraBroker.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        aspen_marketdatafeed::symbol_id symbol_id;
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::reserved_8 reserved_8;
        aspen_marketdatafeed::side side;
        aspen_marketdatafeed::shares shares;
        aspen_marketdatafeed::symbol symbol;
        aspen_marketdatafeed::price price;
        aspen_marketdatafeed::execution_id execution_id;
        aspen_marketdatafeed::broker broker;
        aspen_marketdatafeed::contra_broker contra_broker;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_message};

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
static_assert(offsetof(trade_message::fields_type, symbol_id) == 0, "unexpected offset of trade_message::fields_type::symbol_id");
static_assert(offsetof(trade_message::fields_type, timestamp) == 2, "unexpected offset of trade_message::fields_type::timestamp");
static_assert(offsetof(trade_message::fields_type, reserved_8) == 10, "unexpected offset of trade_message::fields_type::reserved_8");
static_assert(offsetof(trade_message::fields_type, side) == 18, "unexpected offset of trade_message::fields_type::side");
static_assert(offsetof(trade_message::fields_type, shares) == 19, "unexpected offset of trade_message::fields_type::shares");
static_assert(offsetof(trade_message::fields_type, symbol) == 27, "unexpected offset of trade_message::fields_type::symbol");
static_assert(offsetof(trade_message::fields_type, price) == 38, "unexpected offset of trade_message::fields_type::price");
static_assert(offsetof(trade_message::fields_type, execution_id) == 46, "unexpected offset of trade_message::fields_type::execution_id");
static_assert(offsetof(trade_message::fields_type, broker) == 54, "unexpected offset of trade_message::fields_type::broker");
static_assert(offsetof(trade_message::fields_type, contra_broker) == 57, "unexpected offset of trade_message::fields_type::contra_broker");
static_assert(sizeof(trade_message::fields_type) == 60, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(aspen_marketdatafeed::message_header) + 60, "unexpected sizeof trade_message");

#pragma pack(pop)
}
