#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/TerminationCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// TerminateMessage
struct TerminateMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    TerminationCode termination_code;

    // parse method
    static TerminateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TerminateMessage*>(buffer);
    }

    // parse method const
    static const TerminateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TerminateMessage*>(buffer);
    }
};

#pragma pack(pop)
}
