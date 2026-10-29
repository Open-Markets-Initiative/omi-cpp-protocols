#pragma once

#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/EventIndicator.hpp"
#include "../types/MarketSegmentIdOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct OutboundBusinessHeader {

    SessionId session_id;
    MsgSeqNum msg_seq_num;
    SendingTime sending_time;
    EventIndicator event_indicator;
    MarketSegmentIdOptional market_segment_id_optional;

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
