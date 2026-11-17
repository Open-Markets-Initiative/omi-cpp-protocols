// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.1: structs/BidirectionalBusinessHeader.hpp
#pragma once

#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/PossResend.hpp"
#include "../types/MarketSegmentIdOptional.hpp"
#include "../types/PaddingChar2.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

struct BidirectionalBusinessHeader {

    SessionId session_id;
    MsgSeqNum msg_seq_num;
    SendingTime sending_time;
    PossResend poss_resend;
    MarketSegmentIdOptional market_segment_id_optional;
    PaddingChar2 padding_char_2;

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
