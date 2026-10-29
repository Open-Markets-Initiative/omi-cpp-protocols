#pragma once

#include "../types/SessionId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// RetransmissionMessage
struct RetransmissionMessage {

    SessionId session_id;
    RequestTimestamp request_timestamp;
    NextSeqNo next_seq_no;
    Count count;

    // parse method
    static RetransmissionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetransmissionMessage*>(buffer);
    }

    // parse method const
    static const RetransmissionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetransmissionMessage*>(buffer);
    }
};

#pragma pack(pop)
}
