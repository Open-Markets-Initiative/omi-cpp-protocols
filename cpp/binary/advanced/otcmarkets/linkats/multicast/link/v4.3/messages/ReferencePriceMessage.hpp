// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ReferencePriceMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/ReferencePriceId.hpp"
#include "../types/ReferencePriceAction.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidTimeMilli.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Reference Price Message
struct reference_price_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::reference_price_id reference_price_id;
        link_multicast::reference_price_action reference_price_action;
        link_multicast::quote_flags quote_flags;
        link_multicast::security_id security_id;
        link_multicast::ask_price ask_price;
        link_multicast::ask_size ask_size;
        link_multicast::ask_time_milli ask_time_milli;
        link_multicast::bid_price bid_price;
        link_multicast::bid_size bid_size;
        link_multicast::bid_time_milli bid_time_milli;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::reference_price_message};

    fields_type fields;

    // parse method
    static reference_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<reference_price_message*>(buffer);
    }

    // parse method const
    static const reference_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reference_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reference_price_message::fields_type, channel_seq_num) == 0, "unexpected offset of reference_price_message::fields_type::channel_seq_num");
static_assert(offsetof(reference_price_message::fields_type, reference_price_id) == 4, "unexpected offset of reference_price_message::fields_type::reference_price_id");
static_assert(offsetof(reference_price_message::fields_type, reference_price_action) == 8, "unexpected offset of reference_price_message::fields_type::reference_price_action");
static_assert(offsetof(reference_price_message::fields_type, quote_flags) == 9, "unexpected offset of reference_price_message::fields_type::quote_flags");
static_assert(offsetof(reference_price_message::fields_type, security_id) == 10, "unexpected offset of reference_price_message::fields_type::security_id");
static_assert(offsetof(reference_price_message::fields_type, ask_price) == 14, "unexpected offset of reference_price_message::fields_type::ask_price");
static_assert(offsetof(reference_price_message::fields_type, ask_size) == 22, "unexpected offset of reference_price_message::fields_type::ask_size");
static_assert(offsetof(reference_price_message::fields_type, ask_time_milli) == 26, "unexpected offset of reference_price_message::fields_type::ask_time_milli");
static_assert(offsetof(reference_price_message::fields_type, bid_price) == 34, "unexpected offset of reference_price_message::fields_type::bid_price");
static_assert(offsetof(reference_price_message::fields_type, bid_size) == 42, "unexpected offset of reference_price_message::fields_type::bid_size");
static_assert(offsetof(reference_price_message::fields_type, bid_time_milli) == 46, "unexpected offset of reference_price_message::fields_type::bid_time_milli");
static_assert(sizeof(reference_price_message::fields_type) == 54, "unexpected sizeof reference_price_message::fields_type");
static_assert(sizeof(reference_price_message) == sizeof(link_multicast::message_header) + 54, "unexpected sizeof reference_price_message");

#pragma pack(pop)
}
