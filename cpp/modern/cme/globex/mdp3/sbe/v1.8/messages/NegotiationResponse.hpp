#pragma once

#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/SecretKeySecureIdExpiration.hpp"
#include "../types/Padding4.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// NegotiationResponse
struct NegotiationResponse {

    Uuid uuid;
    RequestTimestamp request_timestamp;
    SecretKeySecureIdExpiration secret_key_secure_id_expiration;
    Padding4 padding_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 202;

    // parse method
    static NegotiationResponse* parse(std::byte* buffer) {
        return reinterpret_cast<NegotiationResponse*>(buffer);
    }

    // parse method const
    static const NegotiationResponse* parse(const std::byte* buffer) {
        return reinterpret_cast<const NegotiationResponse*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NegotiationResponse* parse(const MessageHeader* header) {
        return reinterpret_cast<const NegotiationResponse*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
