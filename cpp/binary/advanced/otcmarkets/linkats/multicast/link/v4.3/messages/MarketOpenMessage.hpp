// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/MarketOpenMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/MarketOpen.hpp"
#include "../types/MarketClose.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Market Open Message
struct market_open_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::market_open market_open;
        link_multicast::market_close market_close;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::market_open_message};

    fields_type fields;

    // parse method
    static market_open_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_open_message*>(buffer);
    }

    // parse method const
    static const market_open_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_open_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_open_message::fields_type, channel_seq_num) == 0, "unexpected offset of market_open_message::fields_type::channel_seq_num");
static_assert(offsetof(market_open_message::fields_type, market_open) == 4, "unexpected offset of market_open_message::fields_type::market_open");
static_assert(offsetof(market_open_message::fields_type, market_close) == 12, "unexpected offset of market_open_message::fields_type::market_close");
static_assert(sizeof(market_open_message::fields_type) == 20, "unexpected sizeof market_open_message::fields_type");
static_assert(sizeof(market_open_message) == sizeof(link_multicast::message_header) + 20, "unexpected sizeof market_open_message");

#pragma pack(pop)
}
