#pragma once

#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/PossResend.hpp"
#include "../types/MarketSegmentIdOptional.hpp"
#include "../types/Padding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct BidirectionalBusinessHeader {

    SessionId session_id;
    MsgSeqNum msg_seq_num;
    SendingTime sending_time;
    PossResend poss_resend;
    MarketSegmentIdOptional market_segment_id_optional;
    Padding padding;

    // parse method
    static BidirectionalBusinessHeader* parse(std::byte* buffer) {
        return reinterpret_cast<BidirectionalBusinessHeader*>(buffer);
    }

    // parse method const
    static const BidirectionalBusinessHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const BidirectionalBusinessHeader*>(buffer);
    }
};

#pragma pack(pop)
}
