#pragma once

#include "../types/Reason.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/ErrorCodes.hpp"
#include "../types/Padding5.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// NegotiationReject
struct NegotiationReject {

    Reason reason;
    Uuid uuid;
    RequestTimestamp request_timestamp;
    ErrorCodes error_codes;
    Padding5 padding_5;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 201;

    // parse method
    static NegotiationReject* parse(std::byte* buffer) {
        return reinterpret_cast<NegotiationReject*>(buffer);
    }

    // parse method const
    static const NegotiationReject* parse(const std::byte* buffer) {
        return reinterpret_cast<const NegotiationReject*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NegotiationReject* parse(const MessageHeader* header) {
        return reinterpret_cast<const NegotiationReject*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
