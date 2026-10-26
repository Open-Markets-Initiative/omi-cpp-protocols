#pragma once

#include "../types/RejectReasonCode.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

#pragma pack(push, 1)

// Sent by the Tops Snap server to the client when a Snapshot Request is rejected
struct ErrorResponseMessage {

    RejectReasonCode reject_reason_code;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'e';

    // parse method
    static ErrorResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ErrorResponseMessage*>(buffer);
    }

    // parse method const
    static const ErrorResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ErrorResponseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ErrorResponseMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ErrorResponseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
