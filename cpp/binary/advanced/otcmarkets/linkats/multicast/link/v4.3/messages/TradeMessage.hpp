// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/TradeMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeAction.hpp"
#include "../types/TradeFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TradeStatus.hpp"
#include "../types/Deprecated.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeTimeMilli.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::trade_id trade_id;
        link_multicast::trade_action trade_action;
        link_multicast::trade_flags trade_flags;
        link_multicast::security_id security_id;
        link_multicast::trade_status trade_status;
        link_multicast::deprecated deprecated;
        link_multicast::trade_price trade_price;
        link_multicast::trade_size trade_size;
        link_multicast::trade_time_milli trade_time_milli;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::trade_message};

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
static_assert(offsetof(trade_message::fields_type, channel_seq_num) == 0, "unexpected offset of trade_message::fields_type::channel_seq_num");
static_assert(offsetof(trade_message::fields_type, trade_id) == 4, "unexpected offset of trade_message::fields_type::trade_id");
static_assert(offsetof(trade_message::fields_type, trade_action) == 8, "unexpected offset of trade_message::fields_type::trade_action");
static_assert(offsetof(trade_message::fields_type, trade_flags) == 9, "unexpected offset of trade_message::fields_type::trade_flags");
static_assert(offsetof(trade_message::fields_type, security_id) == 10, "unexpected offset of trade_message::fields_type::security_id");
static_assert(offsetof(trade_message::fields_type, trade_status) == 14, "unexpected offset of trade_message::fields_type::trade_status");
static_assert(offsetof(trade_message::fields_type, deprecated) == 15, "unexpected offset of trade_message::fields_type::deprecated");
static_assert(offsetof(trade_message::fields_type, trade_price) == 23, "unexpected offset of trade_message::fields_type::trade_price");
static_assert(offsetof(trade_message::fields_type, trade_size) == 31, "unexpected offset of trade_message::fields_type::trade_size");
static_assert(offsetof(trade_message::fields_type, trade_time_milli) == 35, "unexpected offset of trade_message::fields_type::trade_time_milli");
static_assert(sizeof(trade_message::fields_type) == 43, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(link_multicast::message_header) + 43, "unexpected sizeof trade_message");

#pragma pack(pop)
}
