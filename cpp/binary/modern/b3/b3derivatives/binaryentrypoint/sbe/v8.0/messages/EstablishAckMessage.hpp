#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/KeepAliveInterval.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/LastIncomingSeqNo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// EstablishAckMessage
struct EstablishAckMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    RequestTimestamp request_timestamp;
    KeepAliveInterval keep_alive_interval;
    NextSeqNo next_seq_no;
    LastIncomingSeqNo last_incoming_seq_no;

    // parse method
    static EstablishAckMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EstablishAckMessage*>(buffer);
    }

    // parse method const
    static const EstablishAckMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EstablishAckMessage*>(buffer);
    }
};

#pragma pack(pop)
}
