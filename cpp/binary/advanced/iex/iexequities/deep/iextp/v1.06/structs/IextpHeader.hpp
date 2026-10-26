#pragma once

#include <cstddef>
#include "../types/Version.hpp"
#include "../types/Reserved.hpp"
#include "../types/MessageProtocolId.hpp"
#include "../types/ChannelId.hpp"
#include "../types/SessionId.hpp"
#include "../types/PayloadLength.hpp"
#include "../types/MessageCount.hpp"
#include "../types/StreamOffset.hpp"
#include "../types/FirstMessageSequenceNumber.hpp"
#include "../types/SendTime.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

namespace iextp_deep = ::iex::iexequities::deep::iextp::v1_06;

#pragma pack(push, 1)

struct iextp_header {

    iextp_deep::version version;
    iextp_deep::reserved reserved;
    iextp_deep::message_protocol_id message_protocol_id;
    iextp_deep::channel_id channel_id;
    iextp_deep::session_id session_id;
    iextp_deep::payload_length payload_length;
    iextp_deep::message_count message_count;
    iextp_deep::stream_offset stream_offset;
    iextp_deep::first_message_sequence_number first_message_sequence_number;
    iextp_deep::send_time send_time;

    // parse method
    static iextp_header* parse(std::byte* buffer) {
        return reinterpret_cast<iextp_header*>(buffer);
    }

    // parse method const
    static const iextp_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const iextp_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(iextp_header, version) == 0, "unexpected offset of iextp_header::version");
static_assert(offsetof(iextp_header, reserved) == 1, "unexpected offset of iextp_header::reserved");
static_assert(offsetof(iextp_header, message_protocol_id) == 2, "unexpected offset of iextp_header::message_protocol_id");
static_assert(offsetof(iextp_header, channel_id) == 4, "unexpected offset of iextp_header::channel_id");
static_assert(offsetof(iextp_header, session_id) == 8, "unexpected offset of iextp_header::session_id");
static_assert(offsetof(iextp_header, payload_length) == 12, "unexpected offset of iextp_header::payload_length");
static_assert(offsetof(iextp_header, message_count) == 14, "unexpected offset of iextp_header::message_count");
static_assert(offsetof(iextp_header, stream_offset) == 16, "unexpected offset of iextp_header::stream_offset");
static_assert(offsetof(iextp_header, first_message_sequence_number) == 24, "unexpected offset of iextp_header::first_message_sequence_number");
static_assert(offsetof(iextp_header, send_time) == 32, "unexpected offset of iextp_header::send_time");
static_assert(sizeof(iextp_header) == 40, "unexpected sizeof iextp_header");

#pragma pack(pop)
}
