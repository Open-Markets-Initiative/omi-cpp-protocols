#pragma once

#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/Padding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct InboundBusinessHeader {

    SessionId session_id;
    MsgSeqNum msg_seq_num;
    SendingTime sending_time;
    MarketSegmentId market_segment_id;
    Padding padding;

    // parse method
    static InboundBusinessHeader* parse(std::byte* buffer) {
        return reinterpret_cast<InboundBusinessHeader*>(buffer);
    }

    // parse method const
    static const InboundBusinessHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const InboundBusinessHeader*>(buffer);
    }
};

#pragma pack(pop)
}
