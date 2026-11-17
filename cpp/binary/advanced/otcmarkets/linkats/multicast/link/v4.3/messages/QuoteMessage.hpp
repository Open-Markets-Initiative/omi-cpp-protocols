// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/QuoteMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/QuoteId.hpp"
#include "../types/QuoteAction.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Mpid.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskQap.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidQap.hpp"
#include "../types/BidTimeMilli.hpp"
#include "../types/QuoteReferenceId.hpp"
#include "../types/ExtendedQuoteFlags.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Quote Message
struct quote_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::quote_id quote_id;
        link_multicast::quote_action quote_action;
        link_multicast::quote_flags quote_flags;
        link_multicast::security_id security_id;
        link_multicast::mpid mpid;
        link_multicast::ask_price ask_price;
        link_multicast::ask_size ask_size;
        link_multicast::ask_qap ask_qap;
        link_multicast::ask_time_milli ask_time_milli;
        link_multicast::bid_price bid_price;
        link_multicast::bid_size bid_size;
        link_multicast::bid_qap bid_qap;
        link_multicast::bid_time_milli bid_time_milli;
        link_multicast::quote_reference_id quote_reference_id;
        link_multicast::extended_quote_flags extended_quote_flags;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::quote_message};

    fields_type fields;

    // parse method
    static quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_message*>(buffer);
    }

    // parse method const
    static const quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_message::fields_type, channel_seq_num) == 0, "unexpected offset of quote_message::fields_type::channel_seq_num");
static_assert(offsetof(quote_message::fields_type, quote_id) == 4, "unexpected offset of quote_message::fields_type::quote_id");
static_assert(offsetof(quote_message::fields_type, quote_action) == 8, "unexpected offset of quote_message::fields_type::quote_action");
static_assert(offsetof(quote_message::fields_type, quote_flags) == 9, "unexpected offset of quote_message::fields_type::quote_flags");
static_assert(offsetof(quote_message::fields_type, security_id) == 10, "unexpected offset of quote_message::fields_type::security_id");
static_assert(offsetof(quote_message::fields_type, mpid) == 14, "unexpected offset of quote_message::fields_type::mpid");
static_assert(offsetof(quote_message::fields_type, ask_price) == 18, "unexpected offset of quote_message::fields_type::ask_price");
static_assert(offsetof(quote_message::fields_type, ask_size) == 26, "unexpected offset of quote_message::fields_type::ask_size");
static_assert(offsetof(quote_message::fields_type, ask_qap) == 30, "unexpected offset of quote_message::fields_type::ask_qap");
static_assert(offsetof(quote_message::fields_type, ask_time_milli) == 31, "unexpected offset of quote_message::fields_type::ask_time_milli");
static_assert(offsetof(quote_message::fields_type, bid_price) == 39, "unexpected offset of quote_message::fields_type::bid_price");
static_assert(offsetof(quote_message::fields_type, bid_size) == 47, "unexpected offset of quote_message::fields_type::bid_size");
static_assert(offsetof(quote_message::fields_type, bid_qap) == 51, "unexpected offset of quote_message::fields_type::bid_qap");
static_assert(offsetof(quote_message::fields_type, bid_time_milli) == 52, "unexpected offset of quote_message::fields_type::bid_time_milli");
static_assert(offsetof(quote_message::fields_type, quote_reference_id) == 60, "unexpected offset of quote_message::fields_type::quote_reference_id");
static_assert(offsetof(quote_message::fields_type, extended_quote_flags) == 62, "unexpected offset of quote_message::fields_type::extended_quote_flags");
static_assert(sizeof(quote_message::fields_type) == 63, "unexpected sizeof quote_message::fields_type");
static_assert(sizeof(quote_message) == sizeof(link_multicast::message_header) + 63, "unexpected sizeof quote_message");

#pragma pack(pop)
}
