#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EnteringFirm.hpp"
#include "../structs/SemanticVersion.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// NegotiateResponseMessage
struct NegotiateResponseMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    RequestTimestamp request_timestamp;
    EnteringFirm entering_firm;
    SemanticVersion semantic_version;

    // parse method
    static NegotiateResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NegotiateResponseMessage*>(buffer);
    }

    // parse method const
    static const NegotiateResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NegotiateResponseMessage*>(buffer);
    }
};

#pragma pack(pop)
}
