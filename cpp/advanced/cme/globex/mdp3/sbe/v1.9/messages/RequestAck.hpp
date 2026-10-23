#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/MdReqId.hpp"
#include "../types/SubscriptionReqType.hpp"
#include "../types/MdReqIdStatus.hpp"
#include "../types/SecurityGroup.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)
struct request_ack_security_groups_entry {
    sbe_mdp3::security_group security_group;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct request_ack_related_symbol_groups_entry {
    sbe_mdp3::security_id security_id;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Request Ack
struct request_ack {

    struct fields_type {
        sbe_mdp3::md_req_id md_req_id;
        sbe_mdp3::subscription_req_type subscription_req_type;
        sbe_mdp3::md_req_id_status md_req_id_status;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::request_ack, schema_id::enum_type::mdpsessionmgmt, version(9)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<request_ack_security_groups_entry, group_size> request_ack_security_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<request_ack_related_symbol_groups_entry, group_size> request_ack_related_symbol_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static request_ack* parse(std::byte* buffer) {
        return reinterpret_cast<request_ack*>(buffer);
    }

    // parse method const
    static const request_ack* parse(const std::byte* buffer) {
        return reinterpret_cast<const request_ack*>(buffer);
    }

};

// layout verification
static_assert(offsetof(request_ack::fields_type, md_req_id) == 0, "unexpected offset of request_ack::fields_type::md_req_id");
static_assert(offsetof(request_ack::fields_type, subscription_req_type) == 4, "unexpected offset of request_ack::fields_type::subscription_req_type");
static_assert(offsetof(request_ack::fields_type, md_req_id_status) == 5, "unexpected offset of request_ack::fields_type::md_req_id_status");
static_assert(sizeof(request_ack::fields_type) == 6, "unexpected sizeof request_ack::fields_type");

#pragma pack(pop)
}

#include "details/RequestAckWriter.hpp"
#include "details/RequestAckReader.hpp"
