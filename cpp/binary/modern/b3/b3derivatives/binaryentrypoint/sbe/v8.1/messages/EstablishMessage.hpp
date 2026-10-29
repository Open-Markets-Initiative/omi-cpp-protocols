#pragma once

#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/KeepAliveInterval.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/CancelOnDisconnectType.hpp"
#include "../types/Offset33Padding1.hpp"
#include "../types/CodTimeoutWindow.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// EstablishMessage
struct EstablishMessage {

    SessionId session_id;
    SessionVerId session_ver_id;
    Timestamp timestamp;
    KeepAliveInterval keep_alive_interval;
    NextSeqNo next_seq_no;
    CancelOnDisconnectType cancel_on_disconnect_type;
    Offset33Padding1 offset_33_padding_1;
    CodTimeoutWindow cod_timeout_window;

    // parse method
    static EstablishMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EstablishMessage*>(buffer);
    }

    // parse method const
    static const EstablishMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EstablishMessage*>(buffer);
    }
};

#pragma pack(pop)
}
