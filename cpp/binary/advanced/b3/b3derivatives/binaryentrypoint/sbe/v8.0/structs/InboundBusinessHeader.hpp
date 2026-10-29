#pragma once

#include <cstddef>
#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/Padding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

struct inbound_business_header {

    sbe_binaryentrypoint::session_id session_id;
    sbe_binaryentrypoint::msg_seq_num msg_seq_num;
    sbe_binaryentrypoint::sending_time sending_time;
    sbe_binaryentrypoint::market_segment_id market_segment_id;
    sbe_binaryentrypoint::padding padding;

    // parse method
    static inbound_business_header* parse(std::byte* buffer) {
        return reinterpret_cast<inbound_business_header*>(buffer);
    }

    // parse method const
    static const inbound_business_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const inbound_business_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(inbound_business_header, session_id) == 0, "unexpected offset of inbound_business_header::session_id");
static_assert(offsetof(inbound_business_header, msg_seq_num) == 4, "unexpected offset of inbound_business_header::msg_seq_num");
static_assert(offsetof(inbound_business_header, sending_time) == 8, "unexpected offset of inbound_business_header::sending_time");
static_assert(offsetof(inbound_business_header, market_segment_id) == 16, "unexpected offset of inbound_business_header::market_segment_id");
static_assert(offsetof(inbound_business_header, padding) == 17, "unexpected offset of inbound_business_header::padding");
static_assert(sizeof(inbound_business_header) == 18, "unexpected sizeof inbound_business_header");

#pragma pack(pop)
}
