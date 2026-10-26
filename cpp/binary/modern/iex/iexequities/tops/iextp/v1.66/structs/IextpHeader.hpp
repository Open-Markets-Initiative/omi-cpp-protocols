#pragma once

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

namespace iex::iexequities::tops::iextp::v1_66 {

#pragma pack(push, 1)

struct IextpHeader {

    Version version;
    Reserved reserved;
    MessageProtocolId message_protocol_id;
    ChannelId channel_id;
    SessionId session_id;
    PayloadLength payload_length;
    MessageCount message_count;
    StreamOffset stream_offset;
    FirstMessageSequenceNumber first_message_sequence_number;
    SendTime send_time;

    // parse method
    static IextpHeader* parse(std::byte* buffer) {
        return reinterpret_cast<IextpHeader*>(buffer);
    }

    // parse method const
    static const IextpHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const IextpHeader*>(buffer);
    }
};

#pragma pack(pop)
}
