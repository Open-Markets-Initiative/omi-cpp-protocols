#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TransactionTime.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/ExecutedSize.hpp"
#include "../types/Instrument.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeType.hpp"
#include "../types/AuctionType.hpp"
#include "../types/TradeFlags.hpp"
#include "../types/HiddenExecutionIndicator.hpp"
#include "../types/TradeQualifier.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::transaction_time transaction_time;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::executed_size executed_size;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::price price;
        gtp_level2mbo::reserved_8 reserved_8;
        gtp_level2mbo::trade_id trade_id;
        gtp_level2mbo::trade_type trade_type;
        gtp_level2mbo::auction_type auction_type;
        gtp_level2mbo::trade_flags trade_flags;
        gtp_level2mbo::hidden_execution_indicator hidden_execution_indicator;
        gtp_level2mbo::trade_qualifier trade_qualifier;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::trade_message};

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
static_assert(offsetof(trade_message::fields_type, timestamp) == 0, "unexpected offset of trade_message::fields_type::timestamp");
static_assert(offsetof(trade_message::fields_type, transaction_time) == 8, "unexpected offset of trade_message::fields_type::transaction_time");
static_assert(offsetof(trade_message::fields_type, source_venue) == 16, "unexpected offset of trade_message::fields_type::source_venue");
static_assert(offsetof(trade_message::fields_type, executed_size) == 18, "unexpected offset of trade_message::fields_type::executed_size");
static_assert(offsetof(trade_message::fields_type, instrument) == 26, "unexpected offset of trade_message::fields_type::instrument");
static_assert(offsetof(trade_message::fields_type, price) == 34, "unexpected offset of trade_message::fields_type::price");
static_assert(offsetof(trade_message::fields_type, reserved_8) == 42, "unexpected offset of trade_message::fields_type::reserved_8");
static_assert(offsetof(trade_message::fields_type, trade_id) == 50, "unexpected offset of trade_message::fields_type::trade_id");
static_assert(offsetof(trade_message::fields_type, trade_type) == 58, "unexpected offset of trade_message::fields_type::trade_type");
static_assert(offsetof(trade_message::fields_type, auction_type) == 59, "unexpected offset of trade_message::fields_type::auction_type");
static_assert(offsetof(trade_message::fields_type, trade_flags) == 60, "unexpected offset of trade_message::fields_type::trade_flags");
static_assert(offsetof(trade_message::fields_type, hidden_execution_indicator) == 61, "unexpected offset of trade_message::fields_type::hidden_execution_indicator");
static_assert(offsetof(trade_message::fields_type, trade_qualifier) == 62, "unexpected offset of trade_message::fields_type::trade_qualifier");
static_assert(sizeof(trade_message::fields_type) == 63, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(gtp_level2mbo::message_header) + 63, "unexpected sizeof trade_message");

#pragma pack(pop)
}
