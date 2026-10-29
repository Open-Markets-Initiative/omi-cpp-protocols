#pragma once

#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/PossResend.hpp"
#include "../types/Padding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct OutboundBusinessHeader {

    SessionId session_id;
    MsgSeqNum msg_seq_num;
    SendingTime sending_time;
    PossResend poss_resend;
    Padding padding;

    // parse method
    static OutboundBusinessHeader* parse(std::byte* buffer) {
        return reinterpret_cast<OutboundBusinessHeader*>(buffer);
    }

    // parse method const
    static const OutboundBusinessHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const OutboundBusinessHeader*>(buffer);
    }
};

#pragma pack(pop)
}
