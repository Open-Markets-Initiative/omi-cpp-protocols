// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/InsideMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/InsideId.hpp"
#include "../types/InsideAction.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidTimeMilli.hpp"
#include "../types/AskNumPricedMp.hpp"
#include "../types/BidNumPricedMp.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Inside Message
struct inside_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::inside_id inside_id;
        link_multicast::inside_action inside_action;
        link_multicast::quote_flags quote_flags;
        link_multicast::security_id security_id;
        link_multicast::ask_price ask_price;
        link_multicast::ask_size ask_size;
        link_multicast::ask_time_milli ask_time_milli;
        link_multicast::bid_price bid_price;
        link_multicast::bid_size bid_size;
        link_multicast::bid_time_milli bid_time_milli;
        link_multicast::ask_num_priced_mp ask_num_priced_mp;
        link_multicast::bid_num_priced_mp bid_num_priced_mp;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::inside_message};

    fields_type fields;

    // parse method
    static inside_message* parse(std::byte* buffer) {
        return reinterpret_cast<inside_message*>(buffer);
    }

    // parse method const
    static const inside_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const inside_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(inside_message::fields_type, channel_seq_num) == 0, "unexpected offset of inside_message::fields_type::channel_seq_num");
static_assert(offsetof(inside_message::fields_type, inside_id) == 4, "unexpected offset of inside_message::fields_type::inside_id");
static_assert(offsetof(inside_message::fields_type, inside_action) == 8, "unexpected offset of inside_message::fields_type::inside_action");
static_assert(offsetof(inside_message::fields_type, quote_flags) == 9, "unexpected offset of inside_message::fields_type::quote_flags");
static_assert(offsetof(inside_message::fields_type, security_id) == 10, "unexpected offset of inside_message::fields_type::security_id");
static_assert(offsetof(inside_message::fields_type, ask_price) == 14, "unexpected offset of inside_message::fields_type::ask_price");
static_assert(offsetof(inside_message::fields_type, ask_size) == 22, "unexpected offset of inside_message::fields_type::ask_size");
static_assert(offsetof(inside_message::fields_type, ask_time_milli) == 26, "unexpected offset of inside_message::fields_type::ask_time_milli");
static_assert(offsetof(inside_message::fields_type, bid_price) == 34, "unexpected offset of inside_message::fields_type::bid_price");
static_assert(offsetof(inside_message::fields_type, bid_size) == 42, "unexpected offset of inside_message::fields_type::bid_size");
static_assert(offsetof(inside_message::fields_type, bid_time_milli) == 46, "unexpected offset of inside_message::fields_type::bid_time_milli");
static_assert(offsetof(inside_message::fields_type, ask_num_priced_mp) == 54, "unexpected offset of inside_message::fields_type::ask_num_priced_mp");
static_assert(offsetof(inside_message::fields_type, bid_num_priced_mp) == 55, "unexpected offset of inside_message::fields_type::bid_num_priced_mp");
static_assert(sizeof(inside_message::fields_type) == 56, "unexpected sizeof inside_message::fields_type");
static_assert(sizeof(inside_message) == sizeof(link_multicast::message_header) + 56, "unexpected sizeof inside_message");

#pragma pack(pop)
}
