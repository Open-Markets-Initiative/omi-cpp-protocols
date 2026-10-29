#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/UnderlyingSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Underlying Status Message
struct underlying_status_message {

    struct fields_type {
        xdp_deepfeed::source_time source_time;
        xdp_deepfeed::source_time_ns source_time_ns;
        xdp_deepfeed::underlying_index underlying_index;
        xdp_deepfeed::underlying_seq_num underlying_seq_num;
        xdp_deepfeed::security_status security_status;
        xdp_deepfeed::halt_condition halt_condition;
        xdp_deepfeed::reserved_2 reserved_2;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::underlying_status_message};

    fields_type fields;

    // parse method
    static underlying_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_status_message*>(buffer);
    }

    // parse method const
    static const underlying_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(underlying_status_message::fields_type, source_time) == 0, "unexpected offset of underlying_status_message::fields_type::source_time");
static_assert(offsetof(underlying_status_message::fields_type, source_time_ns) == 4, "unexpected offset of underlying_status_message::fields_type::source_time_ns");
static_assert(offsetof(underlying_status_message::fields_type, underlying_index) == 8, "unexpected offset of underlying_status_message::fields_type::underlying_index");
static_assert(offsetof(underlying_status_message::fields_type, underlying_seq_num) == 12, "unexpected offset of underlying_status_message::fields_type::underlying_seq_num");
static_assert(offsetof(underlying_status_message::fields_type, security_status) == 16, "unexpected offset of underlying_status_message::fields_type::security_status");
static_assert(offsetof(underlying_status_message::fields_type, halt_condition) == 17, "unexpected offset of underlying_status_message::fields_type::halt_condition");
static_assert(offsetof(underlying_status_message::fields_type, reserved_2) == 18, "unexpected offset of underlying_status_message::fields_type::reserved_2");
static_assert(sizeof(underlying_status_message::fields_type) == 20, "unexpected sizeof underlying_status_message::fields_type");
static_assert(sizeof(underlying_status_message) == sizeof(xdp_deepfeed::message_header) + 20, "unexpected sizeof underlying_status_message");

#pragma pack(pop)
}
