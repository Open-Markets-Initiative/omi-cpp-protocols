#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;


#pragma pack(push, 1)

// Mdpsessionmgmt Message
struct mdpsessionmgmt_message {

    struct fields_type {
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, {}, schema_id::enum_type::mdpsessionmgmt, version(8)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(sbe_mdp3::message_size);

    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_var_data mdpsessionmgmt_payload() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static mdpsessionmgmt_message* parse(std::byte* buffer) {
        return reinterpret_cast<mdpsessionmgmt_message*>(buffer);
    }

    // parse method const
    static const mdpsessionmgmt_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mdpsessionmgmt_message*>(buffer);
    }

};

// layout verification
static_assert(sizeof(mdpsessionmgmt_message::fields_type) == 1, "unexpected sizeof mdpsessionmgmt_message::fields_type");

#pragma pack(pop)
}

#include "details/MdpsessionmgmtMessageWriter.hpp"
#include "details/MdpsessionmgmtMessageReader.hpp"
