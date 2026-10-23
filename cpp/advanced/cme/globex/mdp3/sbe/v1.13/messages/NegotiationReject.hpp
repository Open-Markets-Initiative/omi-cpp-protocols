#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Reason.hpp"
#include "../types/Uuid.hpp"
#include "../types/RequestTimestamp.hpp"
#include "../types/ErrorCodes.hpp"
#include "../types/Padding5.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

// Negotiation Reject
struct negotiation_reject {

    struct fields_type {
        sbe_mdp3::reason reason;
        sbe_mdp3::uuid uuid;
        sbe_mdp3::request_timestamp request_timestamp;
        sbe_mdp3::error_codes error_codes;
        sbe_mdp3::padding_5 padding_5;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::negotiation_reject, schema_id::enum_type::mdpsessionmgmt, version(13)};

    fields_type fields;

    // parse method
    static negotiation_reject* parse(std::byte* buffer) {
        return reinterpret_cast<negotiation_reject*>(buffer);
    }

    // parse method const
    static const negotiation_reject* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiation_reject*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiation_reject::fields_type, reason) == 0, "unexpected offset of negotiation_reject::fields_type::reason");
static_assert(offsetof(negotiation_reject::fields_type, uuid) == 48, "unexpected offset of negotiation_reject::fields_type::uuid");
static_assert(offsetof(negotiation_reject::fields_type, request_timestamp) == 56, "unexpected offset of negotiation_reject::fields_type::request_timestamp");
static_assert(offsetof(negotiation_reject::fields_type, error_codes) == 64, "unexpected offset of negotiation_reject::fields_type::error_codes");
static_assert(offsetof(negotiation_reject::fields_type, padding_5) == 65, "unexpected offset of negotiation_reject::fields_type::padding_5");
static_assert(sizeof(negotiation_reject::fields_type) == 70, "unexpected sizeof negotiation_reject::fields_type");
static_assert(sizeof(negotiation_reject) == sizeof(sbe_mdp3::message_size) + sizeof(sbe_mdp3::message_header) + 70, "unexpected sizeof negotiation_reject");

#pragma pack(pop)
}
