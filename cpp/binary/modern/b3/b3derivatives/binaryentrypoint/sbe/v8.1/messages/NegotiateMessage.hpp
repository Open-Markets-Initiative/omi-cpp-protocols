#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/OnbehalfFirm.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// NegotiateMessage
struct NegotiateMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    Timestamp timestamp;
    EnteringFirm entering_firm;
    OnbehalfFirm onbehalf_firm;

    // parse method
    static NegotiateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NegotiateMessage*>(buffer);
    }

    // parse method const
    static const NegotiateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NegotiateMessage*>(buffer);
    }
};

#pragma pack(pop)
}
