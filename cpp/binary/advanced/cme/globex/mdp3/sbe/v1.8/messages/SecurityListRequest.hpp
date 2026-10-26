#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/MdReqId.hpp"
#include "../types/SubscriptionReqType.hpp"
#include "../types/SecurityGroup.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/SecurityId.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)
struct security_list_request_security_groups_entry {
    sbe_mdp3::security_group security_group;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct security_list_request_related_symbol_groups_entry {
    sbe_mdp3::security_id security_id;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Security List Request
struct security_list_request {

    struct fields_type {
        sbe_mdp3::md_req_id md_req_id;
        sbe_mdp3::subscription_req_type subscription_req_type;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<security_list_request_security_groups_entry, group_size> security_list_request_security_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<security_list_request_related_symbol_groups_entry, group_size> security_list_request_related_symbol_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static security_list_request* parse(std::byte* buffer) {
        return reinterpret_cast<security_list_request*>(buffer);
    }

    // parse method const
    static const security_list_request* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_list_request*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_list_request::fields_type, md_req_id) == 0, "unexpected offset of security_list_request::fields_type::md_req_id");
static_assert(offsetof(security_list_request::fields_type, subscription_req_type) == 4, "unexpected offset of security_list_request::fields_type::subscription_req_type");
static_assert(sizeof(security_list_request::fields_type) == 5, "unexpected sizeof security_list_request::fields_type");

#pragma pack(pop)
}

#include "details/SecurityListRequestWriter.hpp"
#include "details/SecurityListRequestReader.hpp"
