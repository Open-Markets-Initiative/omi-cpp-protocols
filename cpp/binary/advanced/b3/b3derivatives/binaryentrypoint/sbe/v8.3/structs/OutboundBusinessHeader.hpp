#pragma once

#include <cstddef>
#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/EventIndicator.hpp"
#include "../types/MarketSegmentIdOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

#pragma pack(push, 1)

struct outbound_business_header {

    sbe_binaryentrypoint::session_id session_id;
    sbe_binaryentrypoint::msg_seq_num msg_seq_num;
    sbe_binaryentrypoint::sending_time sending_time;
    sbe_binaryentrypoint::event_indicator event_indicator;
    sbe_binaryentrypoint::market_segment_id_optional market_segment_id_optional;

    // parse method
    static outbound_business_header* parse(std::byte* buffer) {
        return reinterpret_cast<outbound_business_header*>(buffer);
    }

    // parse method const
    static const outbound_business_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const outbound_business_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(outbound_business_header, session_id) == 0, "unexpected offset of outbound_business_header::session_id");
static_assert(offsetof(outbound_business_header, msg_seq_num) == 4, "unexpected offset of outbound_business_header::msg_seq_num");
static_assert(offsetof(outbound_business_header, sending_time) == 8, "unexpected offset of outbound_business_header::sending_time");
static_assert(offsetof(outbound_business_header, event_indicator) == 16, "unexpected offset of outbound_business_header::event_indicator");
static_assert(offsetof(outbound_business_header, market_segment_id_optional) == 17, "unexpected offset of outbound_business_header::market_segment_id_optional");
static_assert(sizeof(outbound_business_header) == 18, "unexpected sizeof outbound_business_header");

#pragma pack(pop)
}
