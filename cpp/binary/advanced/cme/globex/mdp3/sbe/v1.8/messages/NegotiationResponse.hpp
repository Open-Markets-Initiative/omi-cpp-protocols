#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/SecretKeySecureIdExpiration.hpp"
#include "../types/Padding4.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

// Negotiation Response
struct negotiation_response {

    struct fields_type {
        sbe_mdp3::uuid uuid;
        sbe_mdp3::request_timestamp request_timestamp;
        sbe_mdp3::secret_key_secure_id_expiration secret_key_secure_id_expiration;
        sbe_mdp3::padding_4 padding_4;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    fields_type fields;

    // parse method
    static negotiation_response* parse(std::byte* buffer) {
        return reinterpret_cast<negotiation_response*>(buffer);
    }

    // parse method const
    static const negotiation_response* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiation_response*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiation_response::fields_type, uuid) == 0, "unexpected offset of negotiation_response::fields_type::uuid");
static_assert(offsetof(negotiation_response::fields_type, request_timestamp) == 8, "unexpected offset of negotiation_response::fields_type::request_timestamp");
static_assert(offsetof(negotiation_response::fields_type, secret_key_secure_id_expiration) == 16, "unexpected offset of negotiation_response::fields_type::secret_key_secure_id_expiration");
static_assert(offsetof(negotiation_response::fields_type, padding_4) == 18, "unexpected offset of negotiation_response::fields_type::padding_4");
static_assert(sizeof(negotiation_response::fields_type) == 22, "unexpected sizeof negotiation_response::fields_type");
static_assert(sizeof(negotiation_response) == sizeof(sbe_mdp3::message_header) + 22, "unexpected sizeof negotiation_response");

#pragma pack(pop)
}
