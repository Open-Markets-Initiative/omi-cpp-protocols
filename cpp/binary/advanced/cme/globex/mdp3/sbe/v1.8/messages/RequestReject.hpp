#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/MdReqIdOptional.hpp"
#include "../types/MdReqRejReason.hpp"
#include "../types/Text.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

// Request Reject
struct request_reject {

    struct fields_type {
        sbe_mdp3::md_req_id_optional md_req_id_optional;
        sbe_mdp3::md_req_rej_reason md_req_rej_reason;
        sbe_mdp3::text text;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    fields_type fields;

    // parse method
    static request_reject* parse(std::byte* buffer) {
        return reinterpret_cast<request_reject*>(buffer);
    }

    // parse method const
    static const request_reject* parse(const std::byte* buffer) {
        return reinterpret_cast<const request_reject*>(buffer);
    }

};

// layout verification
static_assert(offsetof(request_reject::fields_type, md_req_id_optional) == 0, "unexpected offset of request_reject::fields_type::md_req_id_optional");
static_assert(offsetof(request_reject::fields_type, md_req_rej_reason) == 4, "unexpected offset of request_reject::fields_type::md_req_rej_reason");
static_assert(offsetof(request_reject::fields_type, text) == 5, "unexpected offset of request_reject::fields_type::text");
static_assert(sizeof(request_reject::fields_type) == 105, "unexpected sizeof request_reject::fields_type");
static_assert(sizeof(request_reject) == sizeof(sbe_mdp3::message_header) + 105, "unexpected sizeof request_reject");

#pragma pack(pop)
}
