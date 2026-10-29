#pragma once

#include "../types/SessionId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/FromSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// RetransmitRequestMessage
struct RetransmitRequestMessage {

    SessionId session_id;
    Timestamp timestamp;
    FromSeqNo from_seq_no;
    Count count;

    // parse method
    static RetransmitRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetransmitRequestMessage*>(buffer);
    }

    // parse method const
    static const RetransmitRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetransmitRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
