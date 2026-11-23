// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/FrameHeader.hpp
#pragma once

#include <cstddef>
#include "../types/StartOfFrame.hpp"
#include "../types/ProtocolName.hpp"
#include "../types/ProtocolVersion.hpp"
#include "../types/MessageLength.hpp"
#include "../types/SessionId.hpp"
#include "../types/AckRequiredPossDup.hpp"
#include "../types/NumBody.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

struct frame_header {

    xmt_quantumfeedlevel2::start_of_frame start_of_frame;
    xmt_quantumfeedlevel2::protocol_name protocol_name;
    xmt_quantumfeedlevel2::protocol_version protocol_version;
    xmt_quantumfeedlevel2::message_length message_length;
    xmt_quantumfeedlevel2::session_id session_id;
    xmt_quantumfeedlevel2::ack_required_poss_dup ack_required_poss_dup;
    xmt_quantumfeedlevel2::num_body num_body;

    // parse method
    static frame_header* parse(std::byte* buffer) {
        return reinterpret_cast<frame_header*>(buffer);
    }

    // parse method const
    static const frame_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const frame_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(frame_header, start_of_frame) == 0, "unexpected offset of frame_header::start_of_frame");
static_assert(offsetof(frame_header, protocol_name) == 1, "unexpected offset of frame_header::protocol_name");
static_assert(offsetof(frame_header, protocol_version) == 2, "unexpected offset of frame_header::protocol_version");
static_assert(offsetof(frame_header, message_length) == 3, "unexpected offset of frame_header::message_length");
static_assert(offsetof(frame_header, session_id) == 5, "unexpected offset of frame_header::session_id");
static_assert(offsetof(frame_header, ack_required_poss_dup) == 9, "unexpected offset of frame_header::ack_required_poss_dup");
static_assert(offsetof(frame_header, num_body) == 10, "unexpected offset of frame_header::num_body");
static_assert(sizeof(frame_header) == 11, "unexpected sizeof frame_header");

#pragma pack(pop)
}
