#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/HmacSignature.hpp"
#include "../types/AccessKeyId.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/Session.hpp"
#include "../types/Firm.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

// Negotiate
struct negotiate {

    struct fields_type {
        sbe_mdp3::hmac_signature hmac_signature;
        sbe_mdp3::access_key_id access_key_id;
        sbe_mdp3::uuid uuid;
        sbe_mdp3::request_timestamp request_timestamp;
        sbe_mdp3::session session;
        sbe_mdp3::firm firm;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    fields_type fields;

    // parse method
    static negotiate* parse(std::byte* buffer) {
        return reinterpret_cast<negotiate*>(buffer);
    }

    // parse method const
    static const negotiate* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiate*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiate::fields_type, hmac_signature) == 0, "unexpected offset of negotiate::fields_type::hmac_signature");
static_assert(offsetof(negotiate::fields_type, access_key_id) == 32, "unexpected offset of negotiate::fields_type::access_key_id");
static_assert(offsetof(negotiate::fields_type, uuid) == 52, "unexpected offset of negotiate::fields_type::uuid");
static_assert(offsetof(negotiate::fields_type, request_timestamp) == 60, "unexpected offset of negotiate::fields_type::request_timestamp");
static_assert(offsetof(negotiate::fields_type, session) == 68, "unexpected offset of negotiate::fields_type::session");
static_assert(offsetof(negotiate::fields_type, firm) == 73, "unexpected offset of negotiate::fields_type::firm");
static_assert(sizeof(negotiate::fields_type) == 78, "unexpected sizeof negotiate::fields_type");
static_assert(sizeof(negotiate) == sizeof(sbe_mdp3::message_header) + 78, "unexpected sizeof negotiate");

#pragma pack(pop)
}
