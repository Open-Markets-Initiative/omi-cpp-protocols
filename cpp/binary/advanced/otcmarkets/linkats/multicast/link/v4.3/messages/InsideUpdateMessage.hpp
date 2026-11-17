// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/InsideUpdateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/InsideId.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/InsideTimeMilli.hpp"
#include "../types/NumPricedMp.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Inside Update Message
struct inside_update_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::inside_id inside_id;
        link_multicast::quote_flags quote_flags;
        link_multicast::price price;
        link_multicast::size_type size;
        link_multicast::inside_time_milli inside_time_milli;
        link_multicast::num_priced_mp num_priced_mp;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::inside_update_message};

    fields_type fields;

    // parse method
    static inside_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<inside_update_message*>(buffer);
    }

    // parse method const
    static const inside_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const inside_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(inside_update_message::fields_type, channel_seq_num) == 0, "unexpected offset of inside_update_message::fields_type::channel_seq_num");
static_assert(offsetof(inside_update_message::fields_type, inside_id) == 4, "unexpected offset of inside_update_message::fields_type::inside_id");
static_assert(offsetof(inside_update_message::fields_type, quote_flags) == 8, "unexpected offset of inside_update_message::fields_type::quote_flags");
static_assert(offsetof(inside_update_message::fields_type, price) == 9, "unexpected offset of inside_update_message::fields_type::price");
static_assert(offsetof(inside_update_message::fields_type, size) == 17, "unexpected offset of inside_update_message::fields_type::size");
static_assert(offsetof(inside_update_message::fields_type, inside_time_milli) == 21, "unexpected offset of inside_update_message::fields_type::inside_time_milli");
static_assert(offsetof(inside_update_message::fields_type, num_priced_mp) == 29, "unexpected offset of inside_update_message::fields_type::num_priced_mp");
static_assert(sizeof(inside_update_message::fields_type) == 30, "unexpected sizeof inside_update_message::fields_type");
static_assert(sizeof(inside_update_message) == sizeof(link_multicast::message_header) + 30, "unexpected sizeof inside_update_message");

#pragma pack(pop)
}
