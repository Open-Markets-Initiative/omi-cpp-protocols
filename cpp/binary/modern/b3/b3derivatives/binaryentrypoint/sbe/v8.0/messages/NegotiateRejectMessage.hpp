#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/EnteringFirmOptional.hpp"
#include "../types/NegotiationRejectCode.hpp"
#include "../types/Offset25Padding3.hpp"
#include "../types/CurrentSessionVerId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// NegotiateRejectMessage
struct NegotiateRejectMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    RequestTimestamp request_timestamp;
    EnteringFirmOptional entering_firm_optional;
    NegotiationRejectCode negotiation_reject_code;
    Offset25Padding3 offset_25_padding_3;
    CurrentSessionVerId current_session_ver_id;

    // parse method
    static NegotiateRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NegotiateRejectMessage*>(buffer);
    }

    // parse method const
    static const NegotiateRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NegotiateRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
