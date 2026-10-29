#pragma once

#include "../types/SessionId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/RetransmitRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// RetransmitRejectMessage
struct RetransmitRejectMessage {

    SessionId session_id;
    RequestTimestamp request_timestamp;
    RetransmitRejectCode retransmit_reject_code;

    // parse method
    static RetransmitRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetransmitRejectMessage*>(buffer);
    }

    // parse method const
    static const RetransmitRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetransmitRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
