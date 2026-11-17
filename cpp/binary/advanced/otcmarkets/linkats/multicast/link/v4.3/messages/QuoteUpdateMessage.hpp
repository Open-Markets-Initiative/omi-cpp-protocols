// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/QuoteUpdateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ChannelSeqNum.hpp"
#include "../types/QuoteId.hpp"
#include "../types/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/Qap.hpp"
#include "../types/QuoteTimeMilli.hpp"
#include "../types/QuoteReferenceId.hpp"
#include "../types/ExtendedQuoteFlags.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

// Quote Update Message
struct quote_update_message {

    struct fields_type {
        link_multicast::channel_seq_num channel_seq_num;
        link_multicast::quote_id quote_id;
        link_multicast::quote_flags quote_flags;
        link_multicast::price price;
        link_multicast::size_type size;
        link_multicast::qap qap;
        link_multicast::quote_time_milli quote_time_milli;
        link_multicast::quote_reference_id quote_reference_id;
        link_multicast::extended_quote_flags extended_quote_flags;
    };

    link_multicast::message_header header = {std::uint16_t(sizeof(link_multicast::message_header) + sizeof(fields_type)), message_type::enum_type::quote_update_message};

    fields_type fields;

    // parse method
    static quote_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_update_message*>(buffer);
    }

    // parse method const
    static const quote_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_update_message::fields_type, channel_seq_num) == 0, "unexpected offset of quote_update_message::fields_type::channel_seq_num");
static_assert(offsetof(quote_update_message::fields_type, quote_id) == 4, "unexpected offset of quote_update_message::fields_type::quote_id");
static_assert(offsetof(quote_update_message::fields_type, quote_flags) == 8, "unexpected offset of quote_update_message::fields_type::quote_flags");
static_assert(offsetof(quote_update_message::fields_type, price) == 9, "unexpected offset of quote_update_message::fields_type::price");
static_assert(offsetof(quote_update_message::fields_type, size) == 17, "unexpected offset of quote_update_message::fields_type::size");
static_assert(offsetof(quote_update_message::fields_type, qap) == 21, "unexpected offset of quote_update_message::fields_type::qap");
static_assert(offsetof(quote_update_message::fields_type, quote_time_milli) == 22, "unexpected offset of quote_update_message::fields_type::quote_time_milli");
static_assert(offsetof(quote_update_message::fields_type, quote_reference_id) == 30, "unexpected offset of quote_update_message::fields_type::quote_reference_id");
static_assert(offsetof(quote_update_message::fields_type, extended_quote_flags) == 32, "unexpected offset of quote_update_message::fields_type::extended_quote_flags");
static_assert(sizeof(quote_update_message::fields_type) == 33, "unexpected sizeof quote_update_message::fields_type");
static_assert(sizeof(quote_update_message) == sizeof(link_multicast::message_header) + 33, "unexpected sizeof quote_update_message");

#pragma pack(pop)
}
