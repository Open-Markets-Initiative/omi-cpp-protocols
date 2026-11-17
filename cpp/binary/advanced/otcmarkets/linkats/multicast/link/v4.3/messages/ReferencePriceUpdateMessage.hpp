// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ReferencePriceUpdateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/ReferencePriceId.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/TimeMilli.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Reference Price Update Message
struct reference_price_update_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::reference_price_id reference_price_id;
        link_multicast::quote_flags quote_flags;
        link_multicast::price price;
        link_multicast::size_type size;
        link_multicast::time_milli time_milli;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::reference_price_update_message};

    fields_type fields;

    // parse method
    static reference_price_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<reference_price_update_message*>(buffer);
    }

    // parse method const
    static const reference_price_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reference_price_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reference_price_update_message::fields_type, channel_seq_num) == 0, "unexpected offset of reference_price_update_message::fields_type::channel_seq_num");
static_assert(offsetof(reference_price_update_message::fields_type, reference_price_id) == 4, "unexpected offset of reference_price_update_message::fields_type::reference_price_id");
static_assert(offsetof(reference_price_update_message::fields_type, quote_flags) == 8, "unexpected offset of reference_price_update_message::fields_type::quote_flags");
static_assert(offsetof(reference_price_update_message::fields_type, price) == 9, "unexpected offset of reference_price_update_message::fields_type::price");
static_assert(offsetof(reference_price_update_message::fields_type, size) == 17, "unexpected offset of reference_price_update_message::fields_type::size");
static_assert(offsetof(reference_price_update_message::fields_type, time_milli) == 21, "unexpected offset of reference_price_update_message::fields_type::time_milli");
static_assert(sizeof(reference_price_update_message::fields_type) == 29, "unexpected sizeof reference_price_update_message::fields_type");
static_assert(sizeof(reference_price_update_message) == sizeof(link_multicast::message_header) + 29, "unexpected sizeof reference_price_update_message");

#pragma pack(pop)
}
