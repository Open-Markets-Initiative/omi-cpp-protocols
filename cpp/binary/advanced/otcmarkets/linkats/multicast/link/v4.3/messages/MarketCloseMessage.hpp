// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/MarketCloseMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/MarketCloseTimeMilli.hpp"
#include "../types/MarketMsgCt.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Market Close Message
struct market_close_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::market_close_time_milli market_close_time_milli;
        link_multicast::market_msg_ct market_msg_ct;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::market_close_message};

    fields_type fields;

    // parse method
    static market_close_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_close_message*>(buffer);
    }

    // parse method const
    static const market_close_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_close_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_close_message::fields_type, channel_seq_num) == 0, "unexpected offset of market_close_message::fields_type::channel_seq_num");
static_assert(offsetof(market_close_message::fields_type, market_close_time_milli) == 4, "unexpected offset of market_close_message::fields_type::market_close_time_milli");
static_assert(offsetof(market_close_message::fields_type, market_msg_ct) == 12, "unexpected offset of market_close_message::fields_type::market_msg_ct");
static_assert(sizeof(market_close_message::fields_type) == 16, "unexpected sizeof market_close_message::fields_type");
static_assert(sizeof(market_close_message) == sizeof(link_multicast::message_header) + 16, "unexpected sizeof market_close_message");

#pragma pack(pop)
}
