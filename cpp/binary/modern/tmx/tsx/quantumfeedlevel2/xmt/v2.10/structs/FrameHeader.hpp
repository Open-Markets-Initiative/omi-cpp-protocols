#pragma once

#include "../types/StartOfFrame.hpp"
#include "../types/ProtocolName.hpp"
#include "../types/ProtocolVersion.hpp"
#include "../types/MessageLength.hpp"
#include "../types/SessionId.hpp"
#include "../types/AckRequiredPossDup.hpp"
#include "../types/NumBody.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

struct FrameHeader {

    StartOfFrame start_of_frame;
    ProtocolName protocol_name;
    ProtocolVersion protocol_version;
    MessageLength message_length;
    SessionId session_id;
    AckRequiredPossDup ack_required_poss_dup;
    NumBody num_body;

    // parse method
    static FrameHeader* parse(std::byte* buffer) {
        return reinterpret_cast<FrameHeader*>(buffer);
    }

    // parse method const
    static const FrameHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const FrameHeader*>(buffer);
    }
};

#pragma pack(pop)
}
