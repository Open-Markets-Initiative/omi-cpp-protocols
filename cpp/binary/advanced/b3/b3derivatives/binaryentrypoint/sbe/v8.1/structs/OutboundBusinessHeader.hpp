#pragma once

#include <cstddef>
#include "../types/SessionId.hpp"
#include "../types/MsgSeqNum.hpp"
#include "../types/SendingTime.hpp"
#include "../types/PossResend.hpp"
#include "../types/Padding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

struct outbound_business_header {

    sbe_binaryentrypoint::session_id session_id;
    sbe_binaryentrypoint::msg_seq_num msg_seq_num;
    sbe_binaryentrypoint::sending_time sending_time;
    sbe_binaryentrypoint::poss_resend poss_resend;
    sbe_binaryentrypoint::padding padding;

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
static_assert(offsetof(outbound_business_header, poss_resend) == 16, "unexpected offset of outbound_business_header::poss_resend");
static_assert(offsetof(outbound_business_header, padding) == 17, "unexpected offset of outbound_business_header::padding");
static_assert(sizeof(outbound_business_header) == 18, "unexpected sizeof outbound_business_header");

#pragma pack(pop)
}
